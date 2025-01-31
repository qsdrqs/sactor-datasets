#!/usr/bin/env python3
import os
import shutil
import subprocess

from sactor.thirdparty.c2rust import C2Rust
from sactor.thirdparty.crown import Crown

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
    file_path = os.path.join('./selected_data/argv/', file)
    c2rust = C2Rust(file_path)
    c2rust_code = c2rust.get_c2rust_translation()

    crown = Crown(f'/tmp/crown/{file}')
    crown.analyze(c2rust_code) # run preprocessor and analyze the code

    CROWN_RUST_VERSION = "nightly-2023-01-26"
    cmd_prefix = ['rustup', 'run',
                  # Version that works with crown
                  f'{CROWN_RUST_VERSION}-x86_64-unknown-linux-gnu', 'crown']
    cmd = [
        *cmd_prefix,
        os.path.join(crown.analysis_build_path, "src/lib.rs"),
        'rewrite',
        '--results-path',
        crown.analysis_results_path,
        'in-place',
    ]

    subprocess.run(cmd, capture_output=True)

    os.makedirs(os.path.join(target_dir, file), exist_ok=True)
    shutil.copyfile(os.path.join(crown.analysis_build_path, "src/crown_analysis.rs"), os.path.join(target_dir, file, 'lib.rs'))
