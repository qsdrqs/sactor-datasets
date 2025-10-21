#!/usr/bin/env python3
import sys

file = sys.argv[1]
total_unsafe_fraction = 0
with open(file, 'r') as f:
    lines = f.readlines()
    total = len(lines) - 1
    unsafe = 0
    for line in lines:
        line = line.strip()
        cols = line.split(',')
        if cols[3] == 'unsafe_fraction':
            continue
        unsafe_fraction = float(cols[3])
        total_unsafe_fraction += unsafe_fraction
        if unsafe_fraction > 0:
            unsafe += 1

unsafe_fraction = total_unsafe_fraction / total
print(f"{file}: Total: {total}, Unsafe free fraction: {(total - unsafe) / total}, Average unsafe fraction: {unsafe_fraction}")
