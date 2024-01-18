#!/usr/bin/python3


def cover(a, b, intervals):
    # sort intervals by start
    sorted_intervals = sorted(intervals, key=lambda x: x[0])
    unsorted_indices = []

    # Find initial interval that covers a and stretches as far right as possible
    initial_candidates = [x for x in sorted_intervals if x[0] <= a]
    if len(initial_candidates) == 0:
        return "impossible"

    interval_1 = max(initial_candidates, key=lambda x: x[1])
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
