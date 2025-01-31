#!/usr/bin/env python3
'''
Run the translation on the whole program in one go.
'''

import json
import os

from sactor import Sactor
from sactor import utils
from sactor.verifier import VerifyResult

MAX_ATTEMPTS = 6

files = os.listdir('./selected_data/argv')

os.makedirs('./translated_data', exist_ok=True)

success_count = 0
failed_count = 0

total_limit = 100

def dump_failure_info(translated_path, error):
    data = []
    if os.path.exists(os.path.join(translated_path, 'failure_info.json')):
        with open(os.path.join(translated_path, 'failure_info.json'), 'r') as f:
            data = json.load(f)
    data.append({
        'error': error,
    })
    with open(os.path.join(translated_path, 'failure_info.json'), 'w') as f:
        json.dump(data, f)

def translate(c_code, file, file_path, test_cmd_path, translated_path):
    try:
        sactor = Sactor(
            file_path,
            test_cmd_path,
            is_executable=True,
            result_dir=translated_path,
            unidiomatic_only=True,
        )

        llm = sactor.llm
        prompt = f'''
Translate the following C program in idiomatic Rust. No `unsafe` code is allowed.
```c
{c_code}
```
Output the translated function into this format (wrap with the following tags):
----CODE----
```rust
// Your translated function here
```
----END CODE----
'''
        result = llm.query(prompt)
        try:
            translated_code = utils.parse_llm_result(result, "code")
            code = translated_code['code']
        except Exception as e:
            print(f'Failed to parse LLM result: {e}')
            dump_failure_info(translated_path, f'Failed to parse LLM result: {e}')
            return False
        os.makedirs(translated_path, exist_ok=True)
        result = sactor.combiner.verifier.e2e_verify(code)
        if result[0] == VerifyResult.SUCCESS:
            with open(os.path.join(translated_path, 'translated.rs'), 'w') as f:
                f.write(code)
            return True
        else:
            print(f'Failed to verify translation {result[0]}: {result[1]}')
            dump_failure_info(translated_path, f'Failed to verify translation {result[0]}: {result[1]}')
            return False

    except Exception as e:
        print(f'Failed to translate {file}: {e}')
        return False

for file in files:
    if not file.endswith('.c'):
        continue
    translated_path = os.path.join('./translated_data/argv', file)
    if os.path.exists(os.path.join(translated_path, 'failure_info.json')):
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

    with open(file_path, 'r') as f:
        c_code = f.read()

    for attempt in range(MAX_ATTEMPTS):
        if translate(c_code, file, file_path, test_cmd_path, translated_path):
            success_count += 1
            break
        else:
            failed_count += 1

    print("Success count: ", success_count)
    print("Failed count: ", failed_count)

    if success_count + failed_count >= total_limit:
        break
