import random

w = [1.3, 0.1, 3.2, 4.6, 2.5]
p = [1, 2, 3, 4, 5]
p3 = []
N = len(w)

index = random.randint(0, N)
beta = 0
w_max = max(w)

for i in range(N):
    beta += random.random() * 2 * w_max
    while w[index] < beta:
        beta -= w[index]
        index = (index + 1) % N
    p3.append(p[index])

p = p3
print(p)

