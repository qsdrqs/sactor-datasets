#!/usr/bin/env python3
import os
import subprocess

dir = './selected_data'
files = os.listdir(dir)

valid_files = []

for file in files:
    if file.endswith('.c'):
        # try to compile the file by gcc
        os.makedirs('/tmp/compile', exist_ok=True)
        res = subprocess.run(['clang', os.path.join(dir, file), '-o', '/tmp/compile/' + file[:-2]], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
        if res.returncode != 0:
            # add .invalid to the file name if it cannot be compiled
            print('Error: ' + file + ' cannot be compiled')
            os.rename(os.path.join(dir, file), os.path.join(dir, file + '.invalid'))
        else:
            valid_files.append(file)

print('Valid files count: ' + str(len(valid_files)))
