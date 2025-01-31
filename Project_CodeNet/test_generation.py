#!/usr/bin/env python3
import os
import subprocess

from sactor.test_generator import ExecutableTestGenerator
from sactor.sactor import Sactor
from sactor.test_generator import TestGeneratorResult

os.makedirs('./generated_tests/scanf', exist_ok=True)
os.makedirs('./generated_tests/argv', exist_ok=True)
os.makedirs('./test_tasks/scanf', exist_ok=True)
os.makedirs('./test_tasks/argv', exist_ok=True)

COUNT = 100
print('Generating tests for argv')

for root, dirs, files in os.walk('./selected_data/argv'):
    for file in files:
        genenrated = os.listdir('./test_tasks/argv')
        if len(genenrated) >= COUNT:
            # count limit
            break
        if os.path.exists(f'./generated_tests/argv/{file}.json'):
            print(f'Skipping {file}')
            continue
        print(f'Generating tests for {root}/{file}')

        tempdir = '/tmp/project_codenet'
        os.makedirs(tempdir, exist_ok=True)
        file_no_ext = os.path.splitext(file)[0]

        # Compile the code
        cmd = ['clang', '-o', os.path.join(tempdir, file_no_ext), os.path.join(root, file), '-ftrapv']
        result = subprocess.run(cmd, capture_output=True)
        if result.returncode != 0:
            print(f'Error compiling {file}')
            print(result.stderr.decode())
            continue

        binary_path = os.path.join(tempdir, file_no_ext)
        assert os.path.exists(binary_path)

        test_generator = ExecutableTestGenerator(
            file_path=os.path.join(root, file),
            test_samples=[],
            config_path=None,
            executable=binary_path,
            feed_as_arguments=True,
        )
        result = test_generator.generate_tests(count=10)
        if result == TestGeneratorResult.SUCCESS:
            test_generator.create_test_task(
                task_path=f'./test_tasks/argv/{file}.json',
                test_sample_path=f'./generated_tests/argv/{file}.json'
            )
        else:
            print(f'Error generating tests for {file}')
            with open(f'./generated_tests/argv/{file}.json', 'w') as f:
                f.write('[]')

        os.makedirs('llm_statistic/test_generation/argv', exist_ok=True)
        test_generator.llm.statistic(f'llm_statistic/test_generation/argv/{file}.json')

print('Generating tests for scanf')
for root, dirs, files in os.walk('./selected_data/scanf'):
    for file in files:
        genenrated = os.listdir('./test_tasks/scanf')
        if len(genenrated) >= COUNT:
            # count limit
            break
        if os.path.exists(f'./generated_tests/scanf/{file}.json'):
            print(f'Skipping {file}')
            continue
        print(f'Generating tests for {root}/{file}')

        tempdir = '/tmp/project_codenet'
        os.makedirs(tempdir, exist_ok=True)
        file_no_ext = os.path.splitext(file)[0]

        # Compile the code
        cmd = ['clang', '-o', os.path.join(tempdir, file_no_ext), os.path.join(root, file), '-ftrapv']
        result = subprocess.run(cmd, capture_output=True)
        if result.returncode != 0:
            print(f'Error compiling {file}')
            print(result.stderr.decode())
            continue

        binary_path = os.path.join(tempdir, file_no_ext)
        assert os.path.exists(binary_path)

        test_generator = ExecutableTestGenerator(
            file_path=os.path.join(root, file),
            test_samples=[],
            config_path=None,
            executable=binary_path,
            feed_as_arguments=False,
        )
        result = test_generator.generate_tests(count=10)
        if result == TestGeneratorResult.SUCCESS:
            test_generator.create_test_task(
                task_path=f'./test_tasks/scanf/{file}.json',
                test_sample_path=f'./generated_tests/scanf/{file}.json'
            )
        else:
            print(f'Error generating tests for {file}')
            with open(f'./generated_tests/scanf/{file}.json', 'w') as f:
                f.write('[]')

        os.makedirs('llm_statistic/test_generation/scanf', exist_ok=True)
        test_generator.llm.statistic(f'llm_statistic/test_generation/scanf/{file}.json')
