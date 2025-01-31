#!/usr/bin/env python3
'''
Select test cases from the test suite.

'''

COUNT = 200 # select 200 test cases

import os
import sactor.c_parser as c_parser

files = os.listdir('./raw_data')

with open('banned_list.txt', 'r') as f:
    banned_list = f.readlines()
    banned_list = set([file.strip() for file in banned_list])

loc_table = {}

args= {}

for file in files:
    if not file.endswith('.c') or os.path.basename(file) in banned_list:
        continue
    parser = c_parser.CParser(os.path.join('./raw_data', file))
    f_gold_code = parser.extract_function_code('f_gold')
    if f_gold_code is None:
        exit("Error: f_gold not found in " + file)

    loc_table[file] = len(f_gold_code.split('\n'))

    f_gold = parser.get_function_info('f_gold')

    args[file] = f_gold.arguments


sorted_files = sorted(loc_table.items(), key=lambda x: x[1], reverse=True)

selected_files = [file for file, _ in sorted_files[:COUNT]]

# array_count = 0
# array_files = []
# for selected_file in selected_files:
#     has_array = False
#     for arg in args[selected_file]:
#         if arg[1].find('[') != -1:
#             has_array = True
#             break
#     if has_array:
#         array_files.append(selected_file)
#         array_count += 1
#
# print("Number of test cases with array arguments: " + str(array_count))
#
# sorted_array_files = sorted(array_files, key=lambda x: loc_table[x], reverse=True)
# selected_array_files = sorted_array_files[:COUNT//2]
#
# remaining_files = [file for file in selected_files if file not in array_files]
# remaining_count = COUNT//2
#
# sorted_remaining_files = sorted(remaining_files, key=lambda x: loc_table[x], reverse=True)
#
# selected_files = selected_array_files + sorted_remaining_files[:remaining_count]

# write selected files to selected_data_raw
os.makedirs('./selected_data_raw', exist_ok=True)
for selected_file in selected_files:
    os.system('cp ' + os.path.join('./raw_data', selected_file) + ' ./selected_data_raw/' + selected_file)

# output stat into stat.csv: name, loc, has_array
with open('stat.csv', 'w') as f:
    f.write('name,loc\n')
    for file in files:
        if file.endswith('.c') and os.path.basename(file) not in banned_list:
            f.write(file + ',' + str(loc_table[file]) + '\n')

