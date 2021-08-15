#!/usr/bin/python3

import json
import sys

filename = sys.argv[1]
_fields = sys.argv[2]
output_file = sys.argv[3]
flat = str(sys.argv[4]).lower() == 'true'

result = []
with open(filename, 'r') as f:
    data = json.load(f)

fields = _fields.split(',')

for d in data:
    if flat:
        if d.get(fields[0]) is not None:
            result.append(d[fields[0]])
    else:
        new_d = {}
        added = False
        for field in fields:
            if field in d:
                new_d[field] = d[field]
                added = True

        if added:
            result.append(new_d)

with open(output_file, 'w', encoding='utf8') as f:
    json.dump(result, f, ensure_ascii=False, sort_keys=True, separators=(',', ':'))
