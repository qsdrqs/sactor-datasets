#!/usr/bin/env python3

import json
import os

from sactor import Sactor
from sactor.translator import TranslateResult

scanf_files = os.listdir('./selected_data/scanf')
argv_files = os.listdir('./selected_data/argv')

os.makedirs('./translated_data/scanf', exist_ok=True)
os.makedirs('./translated_data/argv', exist_ok=True)

success_tbl = {}
success_count = 0
failed_count = 0

total_limit = 100

for file in argv_files:
    translated_path = os.path.join('./translated_data/argv', file)
    if not os.path.exists(os.path.join(translated_path, 'translated_code_unidiomatic', 'combined.rs')):
        print(f"Skip: {file} - no unidiomatic code")
        continue
    if os.path.exists(os.path.join(translated_path, 'idiomatic_failure_info.json')):
        print("Skip: ", file)
        continue
    file_path = os.path.join('./selected_data/argv', file)
    test_cmd_path = os.path.join('./test_tasks/argv', f'{file}.json')
    if not os.path.exists(test_cmd_path):
        print(f'Skip: {file} - no test command')
        continue
    with open(test_cmd_path, 'r') as f:
        test_cmd = json.load(f)
        if len(test_cmd) == 0:
            print(f'Skip: {file} - no usable test command')

    print("Processing: ", file)
    try:
        sactor = Sactor(
            file_path,
            test_cmd_path,
            result_dir=translated_path,
            is_executable=True,
            llm_stat=os.path.join(translated_path, 'llm_stat_idiomatic.json'),
        )
        sactor.run()
    except Exception as e:
        # add placeholder for failed translation
        if not os.path.exists(os.path.join(translated_path, 'idiomatic_failure_info.json')):
            os.makedirs(translated_path, exist_ok=True)
            with open(os.path.join(translated_path, 'idiomatic_failure_info.json'), 'w') as f:
                json.dump({'error': str(e)}, f)
        print(e)
        failed_count += 1
        print("Success count: ", success_count)
        print("Failed count: ", failed_count)

        if success_count + failed_count >= total_limit:
            break
        continue

    success_count += 1
    print("Success count: ", success_count)
    print("Failed count: ", failed_count)

    if success_count + failed_count >= total_limit:
        break

