#!/usr/bin/python3
import sys


def find_path(M, distances):
    total_distance = sum(distances)
    max_height = total_distance + 1  # Maximum possible height

    # Initialize DP array
    dp = [[False] * (max_height) for _ in range(M + 1)]
    dp[0][0] = True  # Start at height 0

    # Fill DP array
    for i in range(1, M + 1):
        for j in range(max_height):
            if dp[i - 1][j]:
                if j + distances[i - 1] < max_height:  # Can go up
                    dp[i][j + distances[i - 1]] = True
                if j - distances[i - 1] >= 0:  # Can go down
                    dp[i][j - distances[i - 1]] = True

    # Find the path by tracing back from the lowest possible height
    for final_height in range(max_height):
        if dp[M][final_height]:
            path = []
            current_height = final_height
            for i in range(M, 0, -1):
                if (
                    current_height - distances[i - 1] >= 0
                    and dp[i - 1][current_height - distances[i - 1]]
                ):
                    path.append("D")
                    current_height -= distances[i - 1]
                else:
                    path.append("U")
                    current_height += distances[i - 1]
            return "".join(reversed(path))

    return "IMPOSSIBLE"


# Read input and process each scenario
N = int(input())
for _ in range(N):
    M = int(input())
    distances = list(map(int, input().split()))
    result = find_path(M, distances)
    print(result)
