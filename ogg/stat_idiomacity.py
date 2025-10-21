#!/usr/bin/env python3
import os
import sys
import shutil
import json

from sactor.combiner import ProgramCombiner
from sactor.combiner.partial_combiner import PartialCombiner
from sactor.rust_ast_parser import count_unsafe_tokens


# idiom_dir = r"/home/zhang/code/sactor/experiment/ogg/stat_result/gpt5"
idiom_dir = r"/home/zhang/code/sactor/experiment/ogg/stat_result_idiomatic_intersection_functions/gpt5"

# if len(sys.argv) != 2:
#     print("Usage: stat_idiomacity.py <idiom_dir>")

# idiom_dir = sys.argv[1]

files = os.listdir(idiom_dir)

phatom_combiner = ProgramCombiner.__new__(ProgramCombiner)
phatom_combiner.build_path = '/tmp/phatom_build'
phatom_combiner.clippy_stat = {}
phatom_combiner.is_executable = False
phatom_combiner.source_name = 'lib.rs'

def stat_lib(inputpath: str, resultdir: str, step: str):
    srcpath = os.path.join(inputpath, f'translated_code_{step}', "lib.rs")
    if os.path.exists(srcpath):
        with open(srcpath) as f:
            rust_code = f.read()
        phatom_combiner._stat_warnings_errors(rust_code)
        total, unsafe = count_unsafe_tokens(rust_code)

        print(f"{file}: {total} total tokens, {unsafe} unsafe tokens")
        print(phatom_combiner.clippy_stat)
        os.makedirs(resultdir, exist_ok=True)
        with  open( os.path.join(resultdir, f'{step}_clippy_stat.json'), 'w') as f:
            json.dump(phatom_combiner.clippy_stat, f, indent=4)
        with  open( os.path.join(resultdir, f'{step}_unsafe_stat.json'), 'w') as f:
            json.dump({'fraction': unsafe / total, 'total': total, 'unsafe': unsafe}, f, indent=4)

def stat_one_type(inputpath: str, step: str, ty: str):
    srcpath = os.path.join(inputpath, f'translated_code_{step}', f'{ty}s')
    if os.path.isdir(srcpath):
        fs = os.listdir(srcpath)
        # more than 1 function
        functions = {}
        for f in fs:
            with open(os.path.join(srcpath, f)) as f_:
                functions[f] = f_.read()
    return functions

def stat(inputpath: str, step: str, resultdir: str):
    functions = stat_one_type(inputpath, step, 'function')
    data_types = stat_one_type(inputpath, step, 'struct')
    data_types.update(stat_one_type(inputpath, step, 'global_var'))
    partial_combiner = PartialCombiner(functions, data_types)
    _, rust_code = partial_combiner.combine()
    assert rust_code
    total, unsafe = count_unsafe_tokens(rust_code)
    phatom_combiner._stat_warnings_errors(rust_code)
    print(f"{file}: {total} total tokens, {unsafe} unsafe tokens")
    print(phatom_combiner.clippy_stat)
    os.makedirs(resultdir, exist_ok=True)
    with open( os.path.join(resultdir, f'{step}_clippy_stat.json'), 'w') as f:
        json.dump(phatom_combiner.clippy_stat, f, indent=4)
    with open(os.path.join(resultdir, f'{step}_unsafe_stat.json'), 'w') as f:
        json.dump({'fraction': unsafe / total, 'total': total, 'unsafe': unsafe}, f, indent=4)


for file in files:
    os.makedirs(phatom_combiner.build_path, exist_ok=True)
    resultdir = os.path.join(idiom_dir, 'idiom_stat', file)
    # stat_lib(os.path.join(idiom_dir, file), resultdir, "unidiomatic")
    # stat_lib(os.path.join(idiom_dir, file), resultdir, "idiomatic")
    inputdir = os.path.join(idiom_dir, file,)
    if not os.path.isdir(os.path.join(inputdir, 'translated_code_unidiomatic')):
        continue
    stat(inputdir, "unidiomatic", resultdir)   
    stat(inputdir, "idiomatic", resultdir)   

    # if os.path.isdir(os.path.join(sys.argv[1], file, 'translated_code_idiomatic/functions')):
    #     fs = os.listdir(os.path.join(sys.argv[1], file, 'translated_code_idiomatic/functions'))
    #     rust_code = ''
    #     if len(fs) > 1:
    #         # more than 1 function
    #         functions = {}
    #         for f in fs:
    #             with open(os.path.join(sys.argv[1], file, 'translated_code_idiomatic/functions', f)) as f_:
    #                 functions[f] = f_.read()
    #         partial_combiner = PartialCombiner(functions, {})
    #         _, rust_code = partial_combiner.combine()

    #     else:
    #         with open(os.path.join(sys.argv[1], file, 'translated_code_idiomatic/functions/f_filled.rs')) as f:
    #             rust_code = f.read()

    #     assert rust_code
    #     total, unsafe = count_unsafe_tokens(rust_code)
    #     phatom_combiner._stat_warnings_errors(rust_code)
    #     print(f"{file}: {total} total tokens, {unsafe} unsafe tokens")
    #     print(phatom_combiner.clippy_stat)
    #     os.makedirs(resultdir, exist_ok=True)
    #     with  open( os.path.join(resultdir, 'idiomatic_clippy_stat.json'), 'w') as f:
    #         json.dump(phatom_combiner.clippy_stat, f, indent=4)
    #     with open( os.path.join(resultdir, 'idiomatic_unsafe_stat.json'), 'w') as f:
    #         json.dump({'fraction': unsafe / total, 'total': total, 'unsafe': unsafe}, f, indent=4)

    shutil.rmtree(phatom_combiner.build_path)
