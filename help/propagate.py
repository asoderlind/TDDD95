def propagate_values(A, B):
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


# Example usage
A = {"<b>": "<b>"}
B = {"<b>": "bass", "<a>": "<b>"}

A, B = propagate_values(A, B)
print("A:", A)
print("B:", B)
