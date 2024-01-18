#!/usr/bin/python3


def cover(a, b, intervals):
    # sort intervals by start
    sorted_intervals = sorted(intervals, key=lambda x: x[0])

    # keep track of indices in the original list
    unsorted_indices = []

    # Find all intervals that cover a
    intervals_a = [x for x in sorted_intervals if x[0] <= a]

    # if there are no intervals that cover a, return impossible
    if len(intervals_a) == 0:
        return "impossible"

    # if there are multiple intervals that cover a,
    # choose the one that stretches the furthest right
    interval_1 = max(intervals_a, key=lambda x: x[1])
    sorted_index = sorted_intervals.index(interval_1)

    unsorted_indices = [intervals.index(interval_1)]

    cover = interval_1

    while cover[1] < b:
        candidates = [
            x for x in sorted_intervals[sorted_index + 1 :] if x[0] <= cover[1]
        ]
        if len(candidates) == 0:
            return "impossible"
        next_interval = max(candidates, key=lambda x: x[1])

        # if the best candidate does not extend the cover, return impossible
        if next_interval[1] <= cover[1]:
            return "impossible"
        else:
            sorted_index = sorted_intervals.index(next_interval)
            unsorted_indices.append(intervals.index(next_interval))
            cover = next_interval

    return (
        str(len(unsorted_indices)) + "\n" + " ".join([str(x) for x in unsorted_indices])
    )


if __name__ == "__main__":
    while True:
        try:
            (a, b) = [float(x) for x in input().split()]
            n = int(input())
            component_intervals = []
            for _ in range(n):
                (start, end) = (float(x) for x in input().split())
                component_intervals.append((start, end))
            print(cover(a, b, component_intervals))
        except EOFError:
            break
