#!/usr/bin/env python3
import os
import sys
import json

translated_target = sys.argv[1]

translated_dirs = os.listdir(translated_target)

total = 0
total_fails = 0
success = 0
test_fails = 0
compile_fails = 0

success_in_one = 0
success_in_two = 0
success_in_three = 0
success_in_four = 0
success_in_five = 0
success_in_six = 0

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
        }

for dir in translated_dirs:
    # search f_filled.rs in the dirs
    if not os.path.exists(f'{translated_target}/{dir}/idio_failure_info.json'):
        continue
    if not os.path.exists(f'{translated_target}/{dir}/translated_code_idiomatic/functions/f_filled.rs'):
        total_fails += 1
        with open(f'{translated_target}/{dir}/idio_failure_info.json') as f:
            json_data = json.load(f)
        error_list = json_data['f_filled']['errors']
        if len(error_list) == 0:
            print(dir)
            continue
        if error_list[-1]['type'] == "TEST_ERROR":
            # print(dir)
            test_fails += 1
            continue

        elif error_list[-1]['type'] == "COMPILE_ERROR":
            compile_fails += 1
            continue
        else:
            print("Unknown error")
            print(error_list[-1]['type'])
            sys.exit(1)
    else:
        # Success
        success += 1
        with open(f'{translated_target}/{dir}/idio_failure_info.json') as f:
            json_data = json.load(f)
        error_list = json_data['f_filled']['errors']
        if len(error_list) == 0:
            success_in_one += 1
        elif len(error_list) == 1:
            success_in_two += 1
        elif len(error_list) == 2:
            success_in_three += 1
        elif len(error_list) == 3:
            success_in_four += 1
        elif len(error_list) == 4:
            success_in_five += 1
        elif len(error_list) == 5:
            success_in_six += 1


total = success + total_fails
print(f"Total: {total}")
print(f"Success: {success}")
print(f"Total fails: {total_fails}")
print(f"Test fails: {test_fails}")
print(f"Compile fails: {compile_fails}")
print(f"Success in one: {success_in_one}")
print(f"Success in two: {success_in_two}")
print(f"Success in three: {success_in_three}")
print(f"Success in four: {success_in_four}")
print(f"Success in five: {success_in_five}")
print(f"Success in six: {success_in_six}")
