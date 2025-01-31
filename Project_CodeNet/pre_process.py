#!/usr/bin/env python3
import os
import subprocess
import sys
import tempfile

os.makedirs('./selected_data/scanf', exist_ok=True)
os.makedirs('./selected_data/argv', exist_ok=True)

def can_compile(file):
    with tempfile.TemporaryDirectory() as tmpdirname:
        try:
            subprocess.run(['clang', file, '-o', os.path.join(tmpdirname, 'a.out')], check=True, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
            return True
        except subprocess.CalledProcessError:
            return False

def expand_macro(path, file):
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

    last_include_idx = -1
    for i, line in enumerate(lines):
        if line.strip().startswith('#include'):
            last_include_idx = i

    if last_include_idx != -1:
        lines.insert(last_include_idx + 1, '\n/* SPLIT_HERE */\n')

    with tempfile.TemporaryDirectory() as tmpdir:
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

            parts = result.stdout.split('/* SPLIT_HERE */')
            if len(parts) > 1:
                includes = '\n'.join(
                    line for line in lines[:last_include_idx + 1]) + '\n'
                # Combine with expanded part
                expanded = includes + parts[1]

                if path.find('scanf') != -1:
                    out_path = os.path.join('./selected_data/scanf', file)
                elif path.find('argv') != -1:
                    out_path = os.path.join('./selected_data/argv', file)

                with open(out_path, 'w') as f:
                    f.write(expanded)
                # check if it can compile
                if not can_compile(out_path):
                    print(f"Error processing {path}: cannot compile", file=sys.stderr)

            else:
                print(f"Error processing {path}: no split marker found", file=sys.stderr)

        except subprocess.CalledProcessError as e:
            print(f"Error processing {path}: {e}", file=sys.stderr)


for root, dirs, files in os.walk('./selected_data_raw'):
    for file in files:
        path = os.path.join(root, file)
        expand_macro(path, file)

