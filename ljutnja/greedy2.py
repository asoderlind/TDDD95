#!/usr/bin/python3

M, N = map(int, input().split())
children = []
for i in range(N):
    children.append(int(input()))
children.sort()
children.reverse()

diffs = [0]
q = 0

for i in range(1, N):
    diff = children[i - 1] - children[i]
    if i * diff <= M:
        diffs.append(diff)
        M -= i * diff
    else:
        q = i
        break
else:
    diffs.append(0)
    q = N

s = sum(diffs)
for i in range(q):
    s -= diffs[i]
    children[i] -= s

diff = M // q
for i in range(q):
    children[i] -= diff
for i in range(M % q):
    children[i] -= 1
z = 0
for i in children:
    z += i * i
print(children)
print(z)
