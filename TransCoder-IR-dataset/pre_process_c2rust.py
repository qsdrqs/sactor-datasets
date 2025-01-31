#!/usr/bin/env python3
import os
from sactor.c_parser import CParser

files = os.listdir('./selected_data')
os.makedirs('./selected_data_c2rust', exist_ok=True)

with open('./dataset.txt', 'r') as f:
    dataset = f.readlines()
    dataset = [line.strip() for line in dataset]
    dataset = set(dataset)

for file in files:
    if not file.endswith('.c'):
        continue
    if file not in dataset:
        continue
    parser = CParser(os.path.join('./selected_data', file))
    f_filled = parser.get_function_info('f_filled')
    start_line = f_filled.node.extent.start.line

    with open(os.path.join('./selected_data', file)) as f:
        lines = f.readlines()

    with open(os.path.join('./selected_data_c2rust', file), 'w') as f:
        for i, line in enumerate(lines):
            if i < start_line - 1:
                f.write(line)
            else:
                break

    print(f'Processed {file}')
