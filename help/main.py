#! /usr/bin/python3
import sys
import re


def replace_placeholders(line, placeholder2word):
    words = line.split()
    for w in words:
        if w[0] == "<":
            line = line.replace(w, placeholder2word[w])
    return line.strip()


def replace_with_bar(text):
    pattern = r"\<.*?\>"
    return re.sub(pattern, "bar", text)


def propagate_values(A, B):
    """
    # Example usage
    A = {'<b>': '<b>'}
    B = {'<b>': 'bass', '<a>': '<b>'}

    A, B = propagate_values(A, B)
    returns
    A = {'<b>': 'bass'} and
    B = {'<b>': 'bass', '<a>': 'bass'}
    """
    # Flag to check if any updates are made in a single pass
    updated = True

    while updated:
        updated = False

        # Update values in A using B
        for key in A:
            while A[key] in B and A[key] != B[A[key]]:
                A[key] = B[A[key]]
                updated = True

        # Update values in B using A
        for key in B:
            while B[key] in A and B[key] != A[B[key]]:
                B[key] = A[B[key]]
                updated = True

    return A, B


def find_placeholder_matches(line1, line2):
    words1 = line1.split()
    words2 = line2.split()

    if len(words1) == 0 or len(words2) == 0:
        return "-"

    if len(words1) != len(words2):
        return "-"

    words2adj1 = {}
    words2adj2 = {}

    p2w_top = {}
    p2w_bot = {}

    for w1 in words1:
        if w1 not in words2adj1:
            words2adj1[w1] = []

    for w2 in words2:
        if w2 not in words2adj2:
            words2adj2[w2] = []

    for w1, w2 in zip(words1, words2):
        if w2 not in words2adj1[w1]:
            words2adj1[w1].append(w2)
        if w1 not in words2adj2[w2]:
            words2adj2[w2].append(w1)

    print(words2adj1)
    print(words2adj2)

    # Depth first search
    for key in words2adj1:
        visited = []
        stack = [key]
        while stack:
            node = stack.pop()
            print(node)
            if node not in visited:
                visited.append(node)
                stack.extend(words2adj2[words2adj1[node][0]])

    print(p2w_top)
    print(p2w_bot)

    return "-"


if __name__ == "__main__":
    lines = sys.stdin.readlines()
    numCases = int(lines.pop(0))
    for i in range(numCases):
        top_rows = lines[2 * i]
        bottom_rows = lines[2 * i + 1]
        print(find_placeholder_matches(top_rows, bottom_rows))
