#!/usr/bin/env python3
import subprocess
import json
from sactor import utils

target_prog = "./test"
input_output = []

cmd = ['clang', 'lib/test.o', 'selected_data/url.c', '-o', 'test']
subprocess.run(cmd, check=True)


for i in range(1, 11):
    cmd = [target_prog, str(i)]
    result = subprocess.run(cmd, check=True, capture_output=True)
    if result.stderr.decode() != "":
        print(f"Error: {result.stderr}")
        exit(1)
    input_output.append({
        "input": i,
        "output": utils.normalize_string(result.stdout.decode())
    })

with open("input_output.json", "w") as f:
    json.dump(input_output, f, indent=4)
