#!/usr/bin/python3
import sys
from collections import defaultdict


def depth_first_search(tag):
    stack = [tag]
    visited = set()
    words = set()
    while stack:
        current = stack.pop()
        if current in visited:
            continue
        visited.add(current)
        for i in dic[current]:
            if i.isalpha():
                words.add(i)
            else:
                stack.append(i)
            if len(words) > 1:
                return False, "-"
    if words:
        dic[current] = words
        return True, *words
    dic[tag] = {"default"}
    return True, "default"


if __name__ == "__main__":
    lines = sys.stdin.readlines()
    test_cases = int(lines.pop(0))
    for i in range(0, len(lines), 2):
        line_1 = lines[i].split()
        line_2 = lines[i + 1].replace("<", "(").split()
        if len(line_1) != len(line_2):
            print("-")
            continue
        dic = defaultdict(lambda: set())
        for w1, w2 in zip(line_1, line_2):
            if w1.startswith("<"):
                dic[w1].add(w2)
            if w2.startswith("("):
                dic[w2].add(w1)
        is_valid = True
        output_1 = []
        output_2 = []

        for i, _ in enumerate(line_1):
            if line_1[i].startswith("<"):
                is_valid, output_i = depth_first_search(line_1[i])
                output_1.append(output_i)
            else:
                output_1.append(line_1[i])
            if not is_valid:
                break
            if line_2[i].startswith("("):
                is_valid, output_i = depth_first_search(line_2[i])
                output_2.append(output_i)
            else:
                output_2.append(line_2[i])
            if not is_valid:
                break
        if output_1 != output_2 or not is_valid:
            print("-")
        else:
            print(" ".join(output_1))
