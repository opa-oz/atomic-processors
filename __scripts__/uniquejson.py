#!/usr/bin/python3

import json
import sys

filename = sys.argv[1]
filetype = str(sys.argv[2])
keys = str(sys.argv[3])

with open(filename, 'r') as f:
    data = json.load(f)

unique_list = []

TMP_KEY = "_opa_oz_key"

if not filetype or filetype == '' or filetype == 'array':
    for x in data:
        if x not in unique_list:
            unique_list.append(x)
else:
    keys = keys.split(',')
    for x in data:
        unique_key = [x.get(key) for key in keys]
        unique_key = [x for x in unique_key if x is not None]
        x[TMP_KEY] = unique_key

        is_match_found = False

        match = list(
            filter(lambda x: x[TMP_KEY] == unique_key, unique_list)
        )

        if match and len(match) > 0:
            is_match_found = True

        if not is_match_found:
            unique_list.append(x)

    for x in data:
        del x[TMP_KEY]

with open(filename, 'w') as f:
    json.dump(unique_list, f)
