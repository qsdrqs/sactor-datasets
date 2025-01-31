#!/usr/bin/env python3

import os

from sactor import Sactor

cwd = os.path.abspath(os.path.dirname(__file__))

# translate url
os.makedirs('./result/', exist_ok=True)
sactor = Sactor(
    input_file='./selected_data/url.c',
    test_cmd_path='./test_cmd.json',
    is_executable=False,
    result_dir='./result',
    executable_object=f'{cwd}/lib/test.o',
    llm_stat='./result/llm_stat_idiomatic.json',
)

sactor.run()
