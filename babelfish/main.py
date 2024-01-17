#!/usr/bin/python3
from collections import defaultdict
import sys

if __name__ == "__main__":
    input_lines = sys.stdin.readlines()

    my_dict = defaultdict(lambda: "eh")

    index = input_lines.index("\n")
    dictionary_lines = input_lines[:index]
    input_lines = input_lines[index + 1 :]

    # make dict
    for current_line in dictionary_lines:
        translation, word = current_line.split()
        my_dict[word] = translation

    # print output through the dict
    for current_line in input_lines:
        print(my_dict[current_line.strip()])
