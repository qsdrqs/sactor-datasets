#!/usr/bin/env python3
import os
import json
import sys

# Directories containing the translation results from different tools

target_dir = sys.argv[1]

results = []
unidiomatic_result = []
idiomatic_result = []


for file in os.listdir(target_dir):
    if os.path.exists(os.path.join(target_dir, file, 'clippy_stat.json')):
        clippy_path = os.path.join(target_dir, file, 'clippy_stat.json')
        unsafe_path = os.path.join(target_dir, file, 'unsafe_stat.json')

        with open(clippy_path, 'r') as f:
            clippy = json.load(f)
        with open(unsafe_path, 'r') as f:
            unsafe = json.load(f)
        dead_code = clippy['warnings'].get('dead_code', 0) # ignore dead code warnings
        results.append([file, clippy['total_warnings'] - dead_code, clippy['total_errors'], unsafe['fraction']])

    elif os.path.exists(os.path.join(target_dir, file, 'unidiomatic_clippy_stat.json')):
        unidiomatic_clippy_path = os.path.join(target_dir, file, 'unidiomatic_clippy_stat.json')
        unidiomatic_unsafe_path = os.path.join(target_dir, file, 'unidiomatic_unsafe_stat.json')
        with open(unidiomatic_clippy_path, 'r') as f:
            unidiomatic_clippy = json.load(f)
        with open(unidiomatic_unsafe_path, 'r') as f:
            unidiomatic_unsafe = json.load(f)
        dead_code = unidiomatic_clippy['warnings'].get('dead_code', 0) # ignore dead code warnings
        unidiomatic_result.append([file, unidiomatic_clippy['total_warnings'] - dead_code, unidiomatic_clippy['total_errors'], unidiomatic_unsafe['fraction']])

        if os.path.exists(os.path.join(target_dir, file, 'idiomatic_clippy_stat.json')):
            idiomatic_clippy_path = os.path.join(target_dir, file, 'idiomatic_clippy_stat.json')
            idiomatic_unsafe_path = os.path.join(target_dir, file, 'idiomatic_unsafe_stat.json')

            with open(idiomatic_clippy_path, 'r') as f:
                idiomatic_clippy = json.load(f)
            with open(idiomatic_unsafe_path, 'r') as f:
                idiomatic_unsafe = json.load(f)

            dead_code = idiomatic_clippy['warnings'].get('dead_code', 0) # ignore dead code warnings
            idiomatic_result.append([file, idiomatic_clippy['total_warnings'] - dead_code, idiomatic_clippy['total_errors'], idiomatic_unsafe['fraction']])

assert (len(results) == 0 and len(unidiomatic_result) > 0 and len(idiomatic_result) > 0) \
    or (len(results) > 0 and len(unidiomatic_result) == 0 and len(idiomatic_result) == 0)

if len(results) > 0:
    with open(f'{target_dir}_stat.csv', 'w') as f:
        # write csv
        f.write('program,clippy_warnings,clippy_errors,unsafe_fraction\n')
        for result in results:
            f.write(f'{result[0]},{result[1]},{result[2]},{result[3]}\n')
elif len(unidiomatic_result) > 0:
    with open(f'{target_dir}_unidiomatic_stat.csv', 'w') as f:
        f.write('program,clippy_warnings,clippy_errors,unsafe_fraction\n')
        for result in unidiomatic_result:
            f.write(f'{result[0]},{result[1]},{result[2]},{result[3]}\n')
    with open(f'{target_dir}_idiomatic_stat.csv', 'w') as f:
        f.write('program,clippy_warnings,clippy_errors,unsafe_fraction\n')
        for result in idiomatic_result:
            f.write(f'{result[0]},{result[1]},{result[2]},{result[3]}\n')
