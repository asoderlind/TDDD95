#!/usr/bin/python3


def cover(a, b, intervals):
    # sort intervals by start
    sorted_intervals = sorted(intervals, key=lambda x: x[0])

    # keep track of indices in the original list
    selected_indices = []

    # Find all intervals that cover a
    intervals_a = []
    for i in range(len(sorted_intervals)):
        if sorted_intervals[i][0] <= a:
            intervals_a.append(sorted_intervals[i])
        else:
            break

    # if there are no intervals that cover a, return impossible
    if len(intervals_a) == 0:
        return "impossible"

    # if there are multiple intervals that cover a,
    # choose the one that stretches the furthest right
    interval_1 = max(intervals_a, key=lambda x: x[1])
    sorted_index = sorted_intervals.index(interval_1)

    selected_indices.append(intervals.index(interval_1))

    furthest_end = interval_1[1]

    while furthest_end < b:
        candidates = []
        for i in range(sorted_index + 1, len(sorted_intervals)):
            if sorted_intervals[i][0] <= furthest_end:
                candidates.append(sorted_intervals[i])
            else:
                break
        if len(candidates) == 0:
            return "impossible"
        next_interval = max(candidates, key=lambda x: x[1])

        # if the best candidate does not extend the cover, return impossible
        if next_interval[1] <= furthest_end:
            return "impossible"

        sorted_index = sorted_intervals.index(next_interval)
        selected_indices.append(intervals.index(next_interval))
        furthest_end = next_interval[1]

    return (
        str(len(selected_indices)) + "\n" + " ".join([str(x) for x in selected_indices])
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
