#!/usr/bin/env python3
import sys
import os
import json

dataset = './dataset.txt'
with open(dataset) as f:
    data = f.readlines()
    data = [x.strip() for x in data]

file_path = sys.argv[1]


files = os.listdir(file_path)

csv_output = []

for file in files:
    if not os.path.exists(os.path.join(file_path, file, 'translated_code_idiomatic/functions/f_filled.rs')):
        # print('No idiomatic code for', file)
        continue
    with open(os.path.join(file_path, file, 'llm_stat_unidiomatic.json')) as f:
        unidiomatic = json.load(f)
        unidiomatic_total_queries = unidiomatic['total_queries']
        unidiomatic_total_costed_input_tokens = unidiomatic['total_costed_input_tokens']
        unidiomatic_total_costed_output_tokens = unidiomatic['total_costed_output_tokens']
        unidiomatic_total_costed_tokens = unidiomatic_total_costed_output_tokens + unidiomatic_total_costed_input_tokens
        unidiomatic_total_costed_time = unidiomatic['total_costed_time']
    with open(os.path.join(file_path, file, 'llm_stat_idiomatic.json')) as f:
        idiomatic = json.load(f)
        idiomatic_total_queries = idiomatic['total_queries']
        idiomatic_total_costed_input_tokens = idiomatic['total_costed_input_tokens']
        idiomatic_total_costed_output_tokens = idiomatic['total_costed_output_tokens']
        idiomatic_total_costed_tokens = idiomatic_total_costed_output_tokens + idiomatic_total_costed_input_tokens
        idiomatic_total_costed_time = idiomatic['total_costed_time']

    total_costed_tokens = unidiomatic_total_costed_tokens + idiomatic_total_costed_tokens
    total_costed_time = unidiomatic_total_costed_time + idiomatic_total_costed_time
    total_queries = unidiomatic_total_queries + idiomatic_total_queries

    csv_output.append([file, total_costed_tokens, total_costed_time, total_queries])


average_costed_tokens = sum([x[1] for x in csv_output]) / len(csv_output)
average_costed_time = sum([x[2] for x in csv_output]) / len(csv_output)
average_queries = sum([x[3] for x in csv_output]) / len(csv_output)

print('Total success:', len(csv_output))
print('Average costed tokens:', average_costed_tokens)
print('Average costed time:', average_costed_time)
print('Average queries:', average_queries)

