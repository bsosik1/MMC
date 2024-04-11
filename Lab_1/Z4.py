import pygsl.rng as rng

source_1 = rng.taus()
source_2 = rng.mt19937()

for i in range(2):
    print(source_1.uniform())
