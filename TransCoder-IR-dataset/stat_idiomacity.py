#!/usr/bin/env python3
import os
import sys
import shutil
import json

from sactor.combiner import ProgramCombiner
from sactor.combiner.partial_combiner import PartialCombiner
from sactor.rust_ast_parser import count_unsafe_tokens

if len(sys.argv) != 2:
    print("Usage: stat_idiomacity.py <idiom_dir>")

idiom_dir = sys.argv[1]

files = os.listdir(idiom_dir)

phatom_combiner = ProgramCombiner.__new__(ProgramCombiner)
phatom_combiner.build_path = '/tmp/phatom_build'
phatom_combiner.clippy_stat = {}
phatom_combiner.is_executable = False
phatom_combiner.source_name = 'lib.rs'

os.makedirs(f'{idiom_dir}_idiom_stat', exist_ok=True)
for file in files:
    os.makedirs(phatom_combiner.build_path, exist_ok=True)
    if os.path.exists(os.path.join(sys.argv[1], file, 'lib.rs')):
        with open(os.path.join(sys.argv[1], file, 'lib.rs')) as f:
            rust_code = f.read()
        phatom_combiner._stat_warnings_errors(rust_code)
        total, unsafe = count_unsafe_tokens(rust_code)

        print(f"{file}: {total} total tokens, {unsafe} unsafe tokens")
        print(phatom_combiner.clippy_stat)
        os.makedirs(f'{idiom_dir}_idiom_stat/{file}', exist_ok=True)
        with open(f'{idiom_dir}_idiom_stat/{file}/clippy_stat.json', 'w') as f:
            json.dump(phatom_combiner.clippy_stat, f, indent=4)
        with open(f'{idiom_dir}_idiom_stat/{file}/unsafe_stat.json', 'w') as f:
            json.dump({'fraction': unsafe / total, 'total': total, 'unsafe': unsafe}, f, indent=4)

    if os.path.exists(os.path.join(sys.argv[1], file, 'translated_code_unidiomatic/functions/f_filled.rs')):
        fs = os.listdir(os.path.join(sys.argv[1], file, 'translated_code_unidiomatic/functions'))
        rust_code = ''
        if len(fs) > 1:
            # more than 1 function
            functions = {}
            for f in fs:
                with open(os.path.join(sys.argv[1], file, 'translated_code_unidiomatic/functions', f)) as f_:
                    functions[f] = f_.read()
            partial_combiner = PartialCombiner(functions, {})
            _, rust_code = partial_combiner.combine()

        else:
            with open(os.path.join(sys.argv[1], file, 'translated_code_unidiomatic/functions/f_filled.rs')) as f:
                rust_code = f.read()

        assert rust_code
        total, unsafe = count_unsafe_tokens(rust_code)
        phatom_combiner._stat_warnings_errors(rust_code)
        print(f"{file}: {total} total tokens, {unsafe} unsafe tokens")
        print(phatom_combiner.clippy_stat)
        os.makedirs(f'{idiom_dir}_idiom_stat/{file}', exist_ok=True)
        with open(f'{idiom_dir}_idiom_stat/{file}/unidiomatic_clippy_stat.json', 'w') as f:
            json.dump(phatom_combiner.clippy_stat, f, indent=4)
        with open(f'{idiom_dir}_idiom_stat/{file}/unidiomatic_unsafe_stat.json', 'w') as f:
            json.dump({'fraction': unsafe / total, 'total': total, 'unsafe': unsafe}, f, indent=4)

    if os.path.exists(os.path.join(sys.argv[1], file, 'translated_code_idiomatic/functions/f_filled.rs')):
        fs = os.listdir(os.path.join(sys.argv[1], file, 'translated_code_idiomatic/functions'))
        rust_code = ''
        if len(fs) > 1:
            # more than 1 function
            functions = {}
            for f in fs:
                with open(os.path.join(sys.argv[1], file, 'translated_code_idiomatic/functions', f)) as f_:
                    functions[f] = f_.read()
            partial_combiner = PartialCombiner(functions, {})
            _, rust_code = partial_combiner.combine()

        else:
            with open(os.path.join(sys.argv[1], file, 'translated_code_idiomatic/functions/f_filled.rs')) as f:
                rust_code = f.read()

        assert rust_code
        total, unsafe = count_unsafe_tokens(rust_code)
        phatom_combiner._stat_warnings_errors(rust_code)
        print(f"{file}: {total} total tokens, {unsafe} unsafe tokens")
        print(phatom_combiner.clippy_stat)
        os.makedirs(f'{idiom_dir}_idiom_stat/{file}', exist_ok=True)
        with open(f'{idiom_dir}_idiom_stat/{file}/idiomatic_clippy_stat.json', 'w') as f:
            json.dump(phatom_combiner.clippy_stat, f, indent=4)
        with open(f'{idiom_dir}_idiom_stat/{file}/idiomatic_unsafe_stat.json', 'w') as f:
            json.dump({'fraction': unsafe / total, 'total': total, 'unsafe': unsafe}, f, indent=4)

    shutil.rmtree(phatom_combiner.build_path)
