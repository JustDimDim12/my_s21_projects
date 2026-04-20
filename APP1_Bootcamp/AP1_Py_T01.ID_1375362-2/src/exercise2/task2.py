num = int(input())
n = []
while num > 0:
    n.append(num % 10)
    num //= 10

first = n[:len(n)//2]
if len(n) % 2 == 0:
    second = n[len(n)//2:]
else:
    second = n[len(n)//2+1:]

second = second.copy()
second.reverse()

print (first == second and num >= 0)