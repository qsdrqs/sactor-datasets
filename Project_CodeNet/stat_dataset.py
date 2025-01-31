#!/usr/bin/env python3
import os
import shutil

files = os.listdir('./test_tasks/argv/')
file_list = []
for file in files:
    file_list.append(file.split('.json')[0])

with open('./dataset.txt', 'w') as f:
    f.write('\n'.join(file_list))
