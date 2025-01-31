import os
import shutil
import tempfile
import random
import subprocess
from pygount import SourceAnalysis

from sactor.c_parser import CParser

COUNT = 200  # select 200 test cases

all_c_files = []
# use os.walk to get all c files under ./data

def can_compile(file):
    with tempfile.TemporaryDirectory() as tmpdirname:
        try:
            subprocess.run(['clang', file, '-o', os.path.join(tmpdirname, 'a.out')], check=True, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
            return True
        except subprocess.CalledProcessError:
            return False

def find_element(element, lst, count, exclude=[]):
    out = []
    for file in lst:
        if len(out) >= count:
            break
        with open(file, 'r') as f:
            lines = f.readlines()
            find_str = False
            for line in lines:
                if line.find(element) != -1:
                    # check in comment
                    before = line.split(element)[0]
                    if before.find('//') == -1:
                        find_str = True
                        break

            for line in lines:
                # check exclude
                if any([line.find(e) != -1 for e in exclude]):
                    find_str = False
                    break

            if find_str and can_compile(file):
                print(file)
                out.append(file)

    return out

def select_to_raw():
    for root, dirs, files in os.walk('./data'):
        for file in files:
            if file.endswith('.c'):
                all_c_files.append(os.path.join(root, file))

    print("Total c files: ", len(all_c_files))

    # shuffle the list with seed 42
    random.seed(42)
    random.shuffle(all_c_files)

    # find files with 'scanf'
    scanf_files = find_element('scanf', all_c_files, COUNT * 2, exclude=['argv[1]', 'fopen'])
    # find files with 'argv[1]'
    argv_files = find_element('argv[1]', all_c_files, COUNT * 2, exclude=['scanf', 'getchar', 'getch', 'fopen'])

    print("Total scanf files: ", len(scanf_files))
    print("Total argv files: ", len(argv_files))

    # copy files to ./raw_data
    os.makedirs('./raw_data/scanf', exist_ok=True)
    os.makedirs('./raw_data/argv', exist_ok=True)
    for file in scanf_files:
        os.system(f'cp {file} ./raw_data/scanf')
    for file in argv_files:
        os.system(f'cp {file} ./raw_data/argv')

def collect_loc(file):
    analysis = SourceAnalysis.from_file(file, 'c', encoding='utf-8')
    return analysis.code

def select_from_raw():
    stat = {} # name, loc, type

    scanf_files = os.listdir('./raw_data/scanf')
    argv_files = os.listdir('./raw_data/argv')

    for file in scanf_files:
        # collect loc, ignore blank lines and comments
        loc = collect_loc(os.path.join('./raw_data/scanf', file))
        stat[file] = (os.path.join('./raw_data/scanf', file), loc, 'scanf')

    for file in argv_files:
        loc = collect_loc(os.path.join('./raw_data/argv', file))
        stat[file] = (os.path.join('./raw_data/argv', file), loc, 'argv')

    # sort by loc
    sorted_stat = sorted(stat.items(), key=lambda x: x[1][1], reverse=True)
    with open('stat.csv', 'w') as f:
        f.write('name,loc,type\n')
        for file, (path, loc, type) in sorted_stat:
            f.write(f'{path},{loc},{type}\n')

    # select top COUNT
    os.makedirs('./selected_data_raw/scanf', exist_ok=True)
    os.makedirs('./selected_data_raw/argv', exist_ok=True)

    # select COUNT scanf files
    count = 0
    for i in range(len(sorted_stat)):
        if sorted_stat[i][1][2] == 'scanf':
            shutil.copy(sorted_stat[i][1][0], sorted_stat[i][1][0].replace('raw_data', 'selected_data_raw'))
            count += 1
            if count >= COUNT:
                break
    # select COUNT argv files
    count = 0
    for i in range(len(sorted_stat)):
        if sorted_stat[i][1][2] == 'argv':
            shutil.copy(sorted_stat[i][1][0], sorted_stat[i][1][0].replace('raw_data', 'selected_data_raw'))
            count += 1
            if count >= COUNT:
                break


def main():
    if not os.path.exists('./raw_data'):
        select_to_raw()

    select_from_raw()

if __name__ == '__main__':
    main()
