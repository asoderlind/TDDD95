#! /usr/bin/python3
import sys


def replace_placeholders(line, placeholder2word):
    words = line.split()
    for w in words:
        if w[0] == "<":
            line = line.replace(w, placeholder2word[w])
    return line.strip()


def find_placeholder_matches(line1, line2):
    words1 = line1.split()
    words2 = line2.split()
    placeholder2word1 = {}
    placeholder2word2 = {}
    for w1, w2 in zip(words1, words2):
        if w1[0] == "<":
            placeholder2word1[w1] = w2
        elif w2[0] == "<":
            placeholder2word2[w2] = w1

    new_line1 = replace_placeholders(line1, placeholder2word1)
    new_line2 = replace_placeholders(line2, placeholder2word2)

    if new_line1 == new_line2:
        return new_line1

    return "-"


if __name__ == "__main__":
    lines = sys.stdin.readlines()
    numCases = int(lines.pop(0))
    for i in range(numCases):
        print(find_placeholder_matches(lines[2 * i], lines[2 * i + 1]))
