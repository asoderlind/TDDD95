#!/usr/bin/python3


def knapsack(C, n, values, weights):
    # print("C:", C)
    # print("n:", n)
    # print("values:", values)
    # print("weights:", weights)
    mat = [[0 for _ in range(C + 1)] for _ in range(n + 1)]
    # print("mat:", mat)

    # populate the base cases
    for i in range(n + 1):
        mat[i][0] = 0
    for j in range(C + 1):
        mat[0][j] = 0

    # populate the rest of the matrix
    for item in range(1, n + 1):
        for capacity in range(1, C + 1):
            max_without_item = mat[item - 1][capacity]
            max_with_item = 0
            weight_of_item = weights[item - 1]
            if weight_of_item <= capacity:
                max_with_item = (
                    values[item - 1] + mat[item - 1][capacity - weight_of_item]
                )
                remaining_capacity = capacity - weight_of_item
                max_with_item = max(
                    max_with_item, mat[item - 1][remaining_capacity] + values[item - 1]
                )
            mat[item][capacity] = max(max_without_item, max_with_item)

    # Find the items that were selected
    selected_items = []
    capacity = C
    for item in range(n, 0, -1):
        if mat[item][capacity] != mat[item - 1][capacity]:
            selected_items.append(item - 1)
            capacity -= weights[item - 1]

    return (len(selected_items), sorted(selected_items))


if __name__ == "__main__":
    while True:
        try:
            (C, n) = (int(x) for x in input().split())
            values = []
            weights = []
            for _ in range(n):
                (v, w) = (int(x) for x in input().split())
                values.append(v)
                weights.append(w)

            num_selected_items, selected_items = knapsack(C, n, values, weights)
            print(num_selected_items)
            print(" ".join(str(x) for x in selected_items))
        except EOFError:
            break
