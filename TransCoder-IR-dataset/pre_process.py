#!/usr/bin/env python3

import os
import re

import sactor.c_parser as c_parser

files = os.listdir('./selected_data_raw')
os.makedirs('./selected_data', exist_ok=True)

# change `f_filled` to definition only
f_filled = re.compile(r'.* f_filled \(.*\) \{\}')

for file in files:
    with open(os.path.join('./selected_data_raw', file), 'r') as f:
        if not file.endswith('.c'):
            continue
        file_path = os.path.join('./selected_data_raw', file)
        file_parser = c_parser.CParser(file_path)
        f_gold_code = file_parser.extract_function_code('f_gold')
        assert f_gold_code is not None


        lines = f.readlines()
        lines[0] = '#include <string.h>\n#include <ctype.h>\n' + lines[0]
        for i, line in enumerate(lines):
            if f_filled.match(line):
                # Fill the `f_filled` function
                line = f_gold_code.replace('f_gold', 'f_filled') + '\n'
                lines[i] = line

            # add arguments to main
            if line.find('int main') != -1:
                lines[i] = 'int main(int argc, char *argv[]) {\n'

            # remove for loop
            if line.find('for') != -1 and line.find('len(param0)') != -1 and lines[i + 1].find('{') != -1:
                lines[i] = 'int i = argc > 1 ? atoi(argv[1]) : 0;\n'
                lines[i+1] = '' # remove {

            if line.find('n_success+=1;') != -1 and lines[i + 2].find('else') == -1:
                # add feedback
                f_gold = file_parser.get_function_info('f_gold')
                f_gold_arg_types = f_gold.get_arg_types()
                input_list = []
                output_list = []
                for j, arg_type in enumerate(f_gold_arg_types):
                    if arg_type.find('[]') != -1:
                        input_list.append(f'printf("param{j} (first 1 element): "); print_array(param{j}[i], 1)')
                    else:
                        input_list.append(f'printf("param{j}: %d\\n", param{j}[i])')

                lines[i] = '            return 0;\n'

                lines[i + 1] = lines[i + 1] + f'''
        else {{
            printf("Test failed for input: \\n");
            {';\n            '.join(input_list)};
            printf("Expected: %d\\n", f_gold({', '.join([f'param{k}[i]' for k in range(len(f_gold_arg_types))])}));
            printf("Got: %d\\n", f_filled({', '.join([f'param{k}[i]' for k in range(len(f_gold_arg_types))])}));
            return -1;
        }}
'''

            if line.find('#Results:') != -1:
                line = 'if (n_success != len(param0)) return -1;\n'
                lines[i] = line
                lines[i-1] = '' # remove }

            # process special cases
            if file == 'LARGEST_SUBARRAY_WITH_EQUAL_NUMBER_OF_0S_AND_1S.c':
                if line.find("No such subarray") != -1 and line.find('if') == -1 and line.find('else') == -1:
                    line = 'if (n_success != len(param0)) return -1;\n'
                    lines[i] = line
                    lines[i-1] = '' # remove }

            if line.find('int len (int arr [ ]) {return ((int) (sizeof (arr) / sizeof (arr)[0]));}') != -1:
                line = '#define len(arr) ((int) (sizeof (arr) / sizeof (arr)[0]))\n#define print_array(arr, len) for (int i = 0; i < len; i++) printf("%d ", arr[i]); printf("\\n")\n'
                lines[i] = line


        print(f'Processed {file}')


    with open(os.path.join('./selected_data', file), 'w') as f:
        f.writelines(lines)

