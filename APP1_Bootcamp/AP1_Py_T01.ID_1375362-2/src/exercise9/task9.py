N, x = map(float, input().split())
n = int(N)

koefs = []
for i in range(n+1):
    koefs.append(float(input()))

koef = koefs.copy()
koef.reverse()

count = 0
res = 0
for k in koef[1:]:
    res += k * (count+1)*x**count
    count += 1
print(f'{res:.3f}')