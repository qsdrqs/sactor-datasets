#!/usr/bin/env python3
import os

from sactor.thirdparty.c2rust import C2Rust

dataset = './argv_dataset.txt'
with open(dataset) as f:
    lines = f.readlines()
    lines = set([line.strip() for line in lines])

file_path ='./selected_data/argv/'
files = os.listdir(file_path)
# select files in dataset
files = [file for file in files if file in lines]

target_dir = './translated_data/argv/'

for file in files:
    if os.path.exists(os.path.join(target_dir, file)):
        print('File {} already exists. Skipping'.format(file))
        continue
    print('Translating file: {}'.format(file))
    c2rust = C2Rust(os.path.join('./selected_data/argv', file))
    c2rust_out = c2rust.get_c2rust_translation()
    os.makedirs(os.path.join(target_dir, file), exist_ok=True)
    with open(os.path.join(target_dir, file, 'lib.rs'), 'w') as f:
        f.write(c2rust_out)

