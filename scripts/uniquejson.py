#!/usr/bin/python3

import json
import sys

filename = sys.argv[1]
filetype = str(sys.argv[2])

with open(filename, 'r') as f:
    data = json.load(f)

unique_list = []

if not filetype or filetype == '' or filetype == 'array':
    for x in data:
        if x not in unique_list:
            unique_list.append(x)

with open(filename, 'w') as f:
    json.dump(unique_list, f)
