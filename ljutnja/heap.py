#!/usr/bin/python3
import sys
import heapq

if __name__ == "__main__":
    M, N = map(int, sys.stdin.readline().split())
    children = [-int(sys.stdin.readline()) for _ in range(N)]
    heapq.heapify(children)
    while M > 0:
        max_value = -heapq.heappop(children)
        max_value -= 1
        heapq.heappush(children, -max_value)
        M -= 1

    print(children)
    print(sum(x**2 for x in children))
