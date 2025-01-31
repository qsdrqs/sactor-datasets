#!/usr/bin/env python3

import os

from sactor import Sactor

cwd = os.path.abspath(os.path.dirname(__file__))


# translate avl_data
os.makedirs('./result/avl_data', exist_ok=True)
sactor = Sactor(
    input_file='./selected_data/avl_data.c',
    test_cmd_path='./test_cmd.json',
    is_executable=False,
    result_dir='./result/avl_data',
    executable_object=f'{cwd}/lib/avl_test.o {cwd}/lib/avl_bf.o',
    llm_stat='./result/avl_data/llm_stat_idiomatic.json',
)

sactor.run()

# translate avl_bf
os.makedirs('./result/avl_bf', exist_ok=True)
sactor = Sactor(
    input_file='./selected_data/avl_bf.c',
    test_cmd_path='./test_cmd.json',
    is_executable=False,
    result_dir='./result/avl_bf',
    executable_object=f'{cwd}/lib/avl_test.o {cwd}/lib/avl_data.o',
    llm_stat='./result/avl_bf/llm_stat_idiomatic.json',
)

sactor.run()
