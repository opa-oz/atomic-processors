#!/usr/bin/python3

import json
import random
import sys

records = int(sys.argv[1], 10)
filename = sys.argv[2]
tp = sys.argv[3]
seed = str(sys.argv[4])

random.seed(seed if len(seed) > 1 else "random_seed")

print("Making %d records" % records)
strs = ['Jonathan Joestar', 'Joseph Joestar', 'Johnny Joestar',
        'Josuke Higashikata', 'Giorno Giovanna', 'Jolyne Cujoh', 'Jotaro Kujo']

data = []

for i in range(records):
    if tp == 'string':
        data.append(random.choice(strs))
    elif tp == 'int':
        data.append(random.randint(0, 100))
    else:
        if random.randint(0, 10) > 5:
            data.append(random.choice(strs))
        else:
            data.append(random.randint(0, 100))

with open(filename, 'w') as f:
    json.dump(data, f)
