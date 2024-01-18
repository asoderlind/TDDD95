#!/usr/bin/python3
import numpy as np

N = int(input())
M = []
D = []
for i in range(N):
    M.append(int(input()))
    D.append(np.array([int(x) for x in input().split()]))

# print("N:", N)
# print("M:", M)
# print("D:", D)

for i in range(N):
    # Initialize current_solution
    if M[i] > 2:
        current_solution = np.array([1] + [1] * (M[i] - 2) + [-1])
        # Iterate through all combinations
        for j in range(1 << (M[i] - 2)):
            # Update middle elements of current_solution
            for k in range(1, M[i] - 1):
                current_solution[k] = 1 if (j >> (k - 1)) & 1 == 0 else -1

            product = np.dot(current_solution, D[i])
            # print("product:", product)
            if product == 0:
                print("".join(["U" if x == 1 else "D" for x in current_solution]))
                break
        if product != 0:
            print("IMPOSSIBLE")
    elif M[i] == 2:
        # Handle the case where M[i] is 2 or less
        current_solution = np.array([1, -1])
        if np.dot(current_solution, D[i]) != 0:
            print("IMPOSSIBLE")
        else:
            print("UD")
    else:
        print("IMPOSSIBLE")
