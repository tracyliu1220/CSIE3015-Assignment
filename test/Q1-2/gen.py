import random
import time

random.seed(time.process_time())

n = random.randint(1, 8)
n = 1 << n
print(n)

for i in range(n - 1): 
    print(random.uniform(0, 10), end=' ')
print(random.uniform(0, 10))

for i in range(n - 1): 
    print(random.uniform(0, 10), end=' ')
print(random.uniform(0, 10))
