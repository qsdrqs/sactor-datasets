#!/usr/bin/env python3

import subprocess
import os
import re
import json

work_dir = "/tmp/try_asan"
file_dir = "./selected_data"
os.makedirs(work_dir, exist_ok=True)
files = os.listdir(file_dir)

asan_failed_list = []

for file in files:
    with open(os.path.join('./selected_data', file), 'r') as f:
        if not file.endswith('.c'):
            continue
        lines = f.readlines()

        with open(os.path.join(work_dir, file), 'w') as f:
            f.writelines(lines)

        # compile
        result = subprocess.run(
            ["gcc", "-o", os.path.join(work_dir, file + ".out"), os.path.join(work_dir, file), '-g', '-O0', '-fsanitize=address', '-ftrapv'],
            stdout=subprocess.DEVNULL,
            stderr=subprocess.DEVNULL
        )
        if result.returncode != 0:
            print(f"Failed to compile {file}")
            continue

        # run code
        count = 0
        for i in range(10):
            result = subprocess.run(
                [os.path.join(work_dir, file + ".out"), str(i)],
                stdout=subprocess.PIPE,
                stderr=subprocess.PIPE
            )
            if result.returncode != 0:
                count += 1
                print(f"Failed to run asan on {file} with input {i}")
                asan_failed_list.append({
                    'file': file,
                    'test_number': i,
                    'stderr': result.stderr.decode()
                })
            if count >= 9:
                print(f"Abandon {file}")
                # rename the file to xx.c.asan_fail
                os.rename(os.path.join(file_dir, file), os.path.join(file_dir, file + '.asan_fail'))
                break

with open('asan_fail_list.json', 'w') as f:
    json.dump(asan_failed_list, f, indent=4)

files = os.listdir('./selected_data')
count = 0
for file in files:
    if file.endswith('.c'):
        count += 1

print(f"Total valid files: {count}")
