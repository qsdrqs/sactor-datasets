#!/usr/bin/env python3
import json

succeed_in_one = 0
succeed_in_two = 0
succeed_in_three = 0
succeed_in_four = 0
succeed_in_five = 0
succeed_in_six = 0

keys = {}

with open('./result/unidiomatic_failure_info.json') as f:
    unidiomatic_failure_info = json.load(f)
    for key, value in unidiomatic_failure_info.items():
        if key not in keys:
            keys[key] = value['errors']
        else:
            keys[key] += value['errors']

with open('./result/unidiomatic_failure_info.json.bak') as f:
    unidiomatic_failure_info = json.load(f)
    for key, value in unidiomatic_failure_info.items():
        if key not in keys:
            keys[key] = value['errors']
        else:
            keys[key] += value['errors']

with open('./result/unidiomatic_failure_info.json.bak.1') as f:
    unidiomatic_failure_info = json.load(f)
    for key, value in unidiomatic_failure_info.items():
        if key not in keys:
            keys[key] = value['errors']
        else:
            keys[key] += value['errors']

for key, value in keys.items():
    if len(value) == 0:
        succeed_in_one += 1
    elif len(value) == 1:
        succeed_in_two += 1
    elif len(value) == 2:
        succeed_in_three += 1
    elif len(value) == 3:
        succeed_in_four += 1
    elif len(value) == 4:
        succeed_in_five += 1
    else:
        succeed_in_six += 1


print(keys.keys())
print('Total: ', len(keys))
print('Succeed in one: ', succeed_in_one)
print('Succeed in two: ', succeed_in_two)
print('Succeed in three: ', succeed_in_three)
print('Succeed in four: ', succeed_in_four)
print('Succeed in five: ', succeed_in_five)
print('Succeed in six: ', succeed_in_six)
