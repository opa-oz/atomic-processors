#!/usr/bin/python3

# Cheers to https://gist.github.com/AlanHohn/293c98f9dadfc67443b8078d843d4401
import csv
import random
import sys

records = int(sys.argv[1], 10)
filename = sys.argv[2]
with_holes = str(sys.argv[3]).lower() == 'true'
seed = str(sys.argv[4])

random.seed(seed if len(seed) > 1 else "random_seed")

print("Making %d records" % records)
print(f"Making holes: {with_holes}")

fieldnames = ['id', 'name', 'age', 'city']
writer = csv.DictWriter(open(filename, "w"), fieldnames=fieldnames)

names = ['Deepak', 'Sangeeta', 'Geetika', 'Anubhav', 'Sahil', 'Akshay']
cities = ['Delhi', 'Kolkata', 'Chennai', 'Mumbai']

writer.writerow(dict(zip(fieldnames, fieldnames)))
for i in range(0, records):
    source = [

    ]

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

    writer.writerow(dict(source))
