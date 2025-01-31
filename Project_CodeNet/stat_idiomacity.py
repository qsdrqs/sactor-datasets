#!/usr/bin/env python3
import os
import sys
import shutil
import json

from sactor.combiner import ProgramCombiner
from sactor.rust_ast_parser import count_unsafe_tokens

if len(sys.argv) != 2:
    print("Usage: stat_idiomacity.py <idiom_dir>")

idiom_dir = sys.argv[1]
base_dir = os.path.dirname(idiom_dir)
dataset_name = os.path.basename(idiom_dir)

files = os.listdir(idiom_dir)

phatom_combiner = ProgramCombiner.__new__(ProgramCombiner)
phatom_combiner.build_path = '/tmp/phatom_build'
phatom_combiner.clippy_stat = {}
phatom_combiner.is_executable = False
phatom_combiner.source_name = 'lib.rs'

os.makedirs(f'{base_dir}_idiom_stat/{dataset_name}', exist_ok=True)
for file in files:
    print(f"Processing {file}")
    os.makedirs(phatom_combiner.build_path, exist_ok=True)
    if os.path.exists(os.path.join(idiom_dir, file, 'lib.rs')):
        with open(os.path.join(idiom_dir, file, 'lib.rs')) as f:
            rust_code = f.read()
        phatom_combiner._stat_warnings_errors(rust_code)
        total, unsafe = count_unsafe_tokens(rust_code)

        print(f"{file}: {total} total tokens, {unsafe} unsafe tokens")
        print(phatom_combiner.clippy_stat)
        os.makedirs(f'{base_dir}_idiom_stat/{dataset_name}/{file}', exist_ok=True)
        with open(f'{base_dir}_idiom_stat/{dataset_name}/{file}/clippy_stat.json', 'w') as f:
            json.dump(phatom_combiner.clippy_stat, f, indent=4)
        with open(f'{base_dir}_idiom_stat/{dataset_name}/{file}/unsafe_stat.json', 'w') as f:
            json.dump({'fraction': unsafe / total, 'total': total, 'unsafe': unsafe}, f, indent=4)

    if os.path.exists(os.path.join(idiom_dir, file, 'translated_code_unidiomatic/combined.rs')):
        with open(os.path.join(idiom_dir, file, 'translated_code_unidiomatic/combined.rs')) as f:
            rust_code = f.read()

        assert rust_code
        total, unsafe = count_unsafe_tokens(rust_code)
        phatom_combiner._stat_warnings_errors(rust_code)
        print(f"{file}: {total} total tokens, {unsafe} unsafe tokens")
        print(phatom_combiner.clippy_stat)
        os.makedirs(f'{base_dir}_idiom_stat/{dataset_name}/{file}', exist_ok=True)
        with open(f'{base_dir}_idiom_stat/{dataset_name}/{file}/unidiomatic_clippy_stat.json', 'w') as f:
            json.dump(phatom_combiner.clippy_stat, f, indent=4)
        with open(f'{base_dir}_idiom_stat/{dataset_name}/{file}/unidiomatic_unsafe_stat.json', 'w') as f:
            json.dump({'fraction': unsafe / total, 'total': total, 'unsafe': unsafe}, f, indent=4)

    if os.path.exists(os.path.join(idiom_dir, file, 'translated_code_idiomatic/combined.rs')):
        with open(os.path.join(idiom_dir, file, 'translated_code_idiomatic/combined.rs')) as f:
            rust_code = f.read()

        assert rust_code
        total, unsafe = count_unsafe_tokens(rust_code)
        phatom_combiner._stat_warnings_errors(rust_code)
        print(f"{file}: {total} total tokens, {unsafe} unsafe tokens")
        print(phatom_combiner.clippy_stat)
        os.makedirs(f'{base_dir}_idiom_stat/{dataset_name}/{file}', exist_ok=True)
        with open(f'{base_dir}_idiom_stat/{dataset_name}/{file}/idiomatic_clippy_stat.json', 'w') as f:
            json.dump(phatom_combiner.clippy_stat, f, indent=4)
        with open(f'{base_dir}_idiom_stat/{dataset_name}/{file}/idiomatic_unsafe_stat.json', 'w') as f:
            json.dump({'fraction': unsafe / total, 'total': total, 'unsafe': unsafe}, f, indent=4)

    shutil.rmtree(phatom_combiner.build_path)
