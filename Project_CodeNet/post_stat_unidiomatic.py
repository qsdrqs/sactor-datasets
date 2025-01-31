#!/usr/bin/env python3
import os
import json
import sys

if len(sys.argv) != 2:
    print("Usage: python3 post_stat_unidiomatic.py <translated_data_dir>")
    sys.exit(1)
translated_dir = sys.argv[1]
translated_dirs = os.listdir(translated_dir)

total = 0
total_fails = 0
success = 0
test_fails = 0
compile_fails = 0
sactor_functional_fails = 0

success_in_one = 0
success_in_two = 0
success_in_three = 0
success_more_than_three = 0

tests = {}
with open("./stat.csv") as f:
    lines = f.readlines()
    for i in range(1, len(lines)):
        if i == 0:
            continue
        line = lines[i].strip().split(',')
        tests[line[0]] = {
            'name': line[0],
            'loc': int(line[1]),
            'has_array': True if line[2] == '1' else False,
        }

for dir in translated_dirs:
    # search f_filled.rs in the dirs
    if not os.path.exists(f'{translated_dir}/{dir}/unidiomatic_failure_info.json'):
        continue
    if not os.path.exists(f'{translated_dir}/{dir}/translated_code_unidiomatic/combined.rs'):
        total_fails += 1
        with open(f'{translated_dir}/{dir}/unidiomatic_failure_info.json') as f:
            json_data = json.load(f)

        if len(json_data.keys()) == 1 and list(json_data.keys())[0] == "error":
            sactor_functional_fails += 1
            continue

        max_len = 0
        if len(json_data) > 0:
            max_len = max([len(json_data[k]['errors']) for k in json_data.keys()])
        if max_len == 0:
            print(f'{dir} has no errors but no combined.rs')
            continue

        for k in json_data.keys():
            error_list = json_data[k]['errors']
            if len(error_list) != max_len:
                # error not in this item
                continue
            if error_list[-1]['type'] == "TEST_ERROR":
                # print(dir)
                test_fails += 1
                break

            if error_list[-1]['type'] == "COMPILE_ERROR":
                compile_fails += 1
                break
    else:
        # Success
        success += 1
        with open(f'{translated_dir}/{dir}/unidiomatic_failure_info.json') as f:
            json_data = json.load(f)
        error_lists = []
        for k in json_data.keys():
            error_list = json_data[k]['errors']
            error_lists.append(error_list)
        max_len = 0
        if len(error_lists) > 0:
            max_len = max([len(error_list) for error_list in error_lists])
        if max_len == 0:
            success_in_one += 1
        elif max_len == 1:
            success_in_two += 1
        elif max_len == 2:
            success_in_three += 1
        else:
            success_more_than_three += 1

total = success + total_fails
print(f"Total: {total}")
print(f"Success: {success}")
print(f"Total fails: {total_fails}")
print(f"Test fails: {test_fails}")
print(f"Compile fails: {compile_fails}")
print(f"Sactor functional fails: {sactor_functional_fails}")
print(f"Success in one: {success_in_one}")
print(f"Success in two: {success_in_two}")
print(f"Success in three: {success_in_three}")
print(f"Success more than three: {success_more_than_three}")

