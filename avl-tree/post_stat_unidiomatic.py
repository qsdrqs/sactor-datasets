#!/usr/bin/env python3
import json

succeed_in_one = 0
succeed_in_two = 0
succeed_in_three = 0
succeed_in_four = 0
succeed_in_five = 0
succeed_in_six = 0

with open('./result/avl_bf/unidiomatic_failure_info.json') as f:
    unidiomatic_failure_info = json.load(f)

    for key, value in unidiomatic_failure_info.items():
        fails = len(value['errors'])
        if fails == 0:
            succeed_in_one += 1
        elif fails == 1:
            succeed_in_two += 1
        elif fails == 2:
            succeed_in_three += 1
        elif fails == 3:
            succeed_in_four += 1
        elif fails == 4:
            succeed_in_five += 1
        elif fails == 5:
            succeed_in_six += 1


print('Total: ', len(unidiomatic_failure_info))
print('Succeed in one: ', succeed_in_one)
print('Succeed in two: ', succeed_in_two)
print('Succeed in three: ', succeed_in_three)
print('Succeed in four: ', succeed_in_four)
print('Succeed in five: ', succeed_in_five)
print('Succeed in six: ', succeed_in_six)
