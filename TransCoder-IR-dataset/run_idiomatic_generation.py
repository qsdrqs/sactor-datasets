#!/usr/bin/env python3

import json
import os

from sactor import Sactor
from sactor.translator import TranslateResult

dataset = './dataset.txt'
with open(dataset, 'r') as f:
    data = f.readlines()
    data = set([x.strip() for x in data])
files = os.listdir('./selected_data')

os.makedirs('./translated_data', exist_ok=True)

success_tbl = {}
success_count = 0
failed_count = 0

total_limit = 100

for file in files:
    if not file in data:
        continue
    if not file.endswith('.c'):
        continue
    translated_path = os.path.join('./translated_data', file)
    if os.path.exists(os.path.join(translated_path, 'idio_failure_info.json')):
        print("Skip: ", file)
        continue
    if not os.path.exists(os.path.join(translated_path, 'translated_code_unidiomatic/functions/f_filled.rs')):
        print("Unidiomatic code not found: ", file)
        continue

    file_path = os.path.join('./selected_data', file)
    test_cmd_path = os.path.join('./test_tasks/', f'{file}.json')
    if not os.path.exists(test_cmd_path):
        print(f'Skip: {file} - no test command')
        continue
    with open(test_cmd_path, 'r') as f:
        test_cmd = json.load(f)
        if len(test_cmd) == 0:
            print(f'Skip: {file} - no usable test command')

    try:
        sactor = Sactor(
            file_path,
            test_cmd_path,
            is_executable=True,
            result_dir=translated_path,
        )
        idiomatic_translator = sactor._new_idiomatic_translator()
        parser = sactor.c_parser

        continue_loop = False
        for dependency in parser.get_function_info('f_filled').function_dependencies:
            result = idiomatic_translator.translate_function(
                parser.get_function_info(dependency.name))
            if result != TranslateResult.SUCCESS:
                failed_count += 1
                continue_loop = True
                break
        if not continue_loop:
            result = idiomatic_translator.translate_function(
                parser.get_function_info('f_filled'))
            if result == TranslateResult.SUCCESS:
                success_tbl[file] = result
                success_count += 1
            else:
                failed_count += 1
        idiomatic_translator.save_failure_info(
            os.path.join(translated_path, 'idio_failure_info.json'))
        sactor.llm.statistic(os.path.join(translated_path, 'llm_stat_idiomatic.json'))
    except Exception as e:
        print(f'Failed to translate {file}: {e}')
        # print stack trace
        failed_count += 1

    print("Success count: ", success_count)
    print("Failed count: ", failed_count)

    if success_count + failed_count >= total_limit:
        break
