N, M = map(int, input().split())
a = []
for i in range(N):
    row = (list(map(int, input().split())))
    a.append(row)

for i in range (1, N):
    a[i][0] += a[i-1][0]
    for j in range (1, M):
        a[i][j]+= max(a[i-1][j], a[i][j-1])

print(a[N-1][M-1])