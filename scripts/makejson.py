#!/usr/bin/python3

# Cheers to https://gist.github.com/AlanHohn/293c98f9dadfc67443b8078d843d4401
import json
import random
import sys

records = int(sys.argv[1], 10)
filename = sys.argv[2]
with_holes = str(sys.argv[3]).lower() == 'true'

print("Making %d records" % records)
print(f"Making holes: {with_holes}")

fieldnames = ['id', 'name', 'age', 'city']
names = ['Deepak', 'Sangeeta', 'Geetika', 'Anubhav', 'Sahil', 'Akshay']
cities = ['Delhi', 'Kolkata', 'Chennai', 'Mumbai']

result = []

for i in range(0, records):
    source = []

    if with_holes:
        if random.randint(0, 10) > 3:
            source.append(('id', i))
        if random.randint(0, 10) > 3:
            source.append(('name', random.choice(names)))
        if random.randint(0, 10) > 3:
            source.append(('age', str(random.randint(10, 26))))
        if random.randint(0, 10) > 3:
            source.append(('city', random.choice(cities)))

    else:
        source = [('id', i),
                  ('name', random.choice(names)),
                  ('age', str(random.randint(10, 26))),
                  ('city', random.choice(cities))]

    result.append(dict(source))

with open(filename, 'w') as f:
    json.dump(result, f)
