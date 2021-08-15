#!/usr/bin/python3

import json
import sys

filename = sys.argv[1]
extension = sys.argv[2]
m_type = sys.argv[3]
output_file = sys.argv[4]

result = []
with open(filename, 'r') as f:
    lines = f.read().strip().split('\n')
    for line in lines:
        msg = json.loads(line)['message']
        if msg['type'] == m_type or m_type == 'all':
            result.append(msg)

with open(output_file, 'w', encoding='utf8') as f:
    if extension == 'json':
        json.dump(result, f, ensure_ascii=False, sort_keys=True, separators=(',', ':'))
