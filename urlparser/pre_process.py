#!/usr/bin/env python3
import tempfile
import shutil
import sys
import subprocess
import os
import re

dir = './raw_data'
out_dir = './selected_data'
lib_dir = './lib'
os.makedirs(dir, exist_ok=True)
os.makedirs(out_dir, exist_ok=True)
os.makedirs(lib_dir, exist_ok=True)
copy_files = ['url.c', 'url.h', 'url_char_category.h', 'url_char_category_table.h']

def can_compile(file):
    with tempfile.TemporaryDirectory() as tmpdirname:
        try:
            subprocess.run(['clang', file, '-c', '-o', os.path.join(tmpdirname, 'a.out')], check=True, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
            return True
        except subprocess.CalledProcessError:
            return False

def merge_header(path):
    pattern = re.compile(r'#include\s*"(.*)"')

    with open(f'{dir}/{file}', 'r+') as f:
        lines = f.readlines()
    for i, line in enumerate(lines):
        if pattern.match(line):
            matched = pattern.match(line)
            assert matched is not None
            header = matched.group(1)
            with open(f'{dir}/{header}', 'r') as h:
                header_content = h.read()
            lines[i] = header_content + '\n'
    with open(f'{out_dir}/{file}', 'w') as f:
                f.writelines(lines)

def expand_macro(path):
    file = os.path.basename(path)
    with open(path, 'r') as f:
        content = f.read()

    # Find the last #include line and insert the marker
    lines = content.splitlines()

    # remove #ifdef __cplusplus
    start = -1
    for i, line in enumerate(lines):
        if line.strip().startswith('#ifdef __cplusplus'):
            start = i
        if line.strip().startswith('#endif'):
            if start != -1:
                lines = lines[:start] + lines[i+1:]

    removed_includes = []
    for i, line in enumerate(lines):
        if line.strip().startswith('#include'):
            # remove the include line, to prevent expand macros in the header
            removed_includes.append(line)
            lines[i] = ''

    with tempfile.TemporaryDirectory() as tmpdir:
        tmpdir = '/tmp/expand_macro'
        os.makedirs(tmpdir, exist_ok=True)

        # Write to a temporary file
        with open(os.path.join(tmpdir, file), 'w') as f:
            f.write('\n'.join(lines))

        try:
            # use `cpp -C -P` to expand all macros
            result = subprocess.run(
                ['cpp', '-C', '-P', os.path.join(tmpdir, file)],
                capture_output=True,
                text=True,
                check=True
            )

            # Combine with expanded part
            expanded = '\n'.join(removed_includes) + '\n' + result.stdout

            out_path = path

            with open(out_path, 'w') as f:
                f.write(expanded)
            # check if it can compile
            if not can_compile(out_path):
                print(f"Error processing {path}: cannot compile", file=sys.stderr)


        except subprocess.CalledProcessError as e:
            print(f"Error processing {path}: {e}", file=sys.stderr)

for file in copy_files:
    shutil.copyfile(f'url.h/{file}', f'{dir}/{file}')

files = os.listdir(dir)
for file in files:
    if file.endswith('.c'):
        print(f'Processing {file}')
        merge_header(f'{dir}/{file}')
        expand_macro(f'{out_dir}/{file}')


# compile test object file
cmd = ['clang', '-c', '-o', f'{lib_dir}/test.o', f'url.h/test.c']
subprocess.run(cmd, check=True)
