#!/usr/bin/env python3
import os

from sactor.thirdparty.c2rust import C2Rust

files = os.listdir('./selected_data_c2rust')
target_dir = './translated_data'
os.makedirs(target_dir, exist_ok=True)

for file in files:
    print('Translating file: {}'.format(file))
    c2rust = C2Rust(os.path.join('./selected_data_c2rust', file))
    c2rust_out = c2rust.get_c2rust_translation()
    os.makedirs(os.path.join(target_dir, file), exist_ok=True)
    with open(os.path.join(target_dir, file, 'lib.rs'), 'w') as f:
        f.write(c2rust_out)

