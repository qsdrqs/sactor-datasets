import os
import json

files = os.listdir('./selected_data')
os.makedirs('./test_tasks', exist_ok=True)

with open('./asan_fail_list.json') as f:
    asan_fail_list = json.load(f)

with open('./valgrind_fail_list.json') as f:
    valgrind_fail_list = json.load(f)

def search_asan_valgrind(file, number):
    for item in asan_fail_list:
        if item['file'] == file and item['test_number'] == number:
            return True
    for item in valgrind_fail_list:
        if item['file'] == file and item['test_number'] == number:
            return True
    return False

for file in files:
    if not file.endswith('.c'):
        continue
    if file in asan_fail_list:
        continue
    output_file = os.path.join('./test_tasks', f'{file}.json')
    output = []
    for i in range(10):
        if search_asan_valgrind(file, i):
            continue
        output.append({
            'command': f"%t {i}",
        })

    with open(output_file, 'w') as f:
        json.dump(output, f, indent=4)
