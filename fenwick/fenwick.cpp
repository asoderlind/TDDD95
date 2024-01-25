/** TDDD95: Lab 1 - fenwick
 * Author: Axel Söderlind
 * Date:   2024-01-25
 * This problem is about implementing a Binary Indexed Tree (BIT),
 * also known as Fenwick Tree. We use the BIT class to solve this
 * problem. We initialize the BIT with n elements, each with value 0.
 * We then iterate through the queries and perform the appropriate
 * operation for each query.
 *
 * Complexity: O(logn) where n is the number of elements and q is the number of queries.
 * Space: O(n) where n is the number of elements.
 */
#include <iostream>
#include <vector>

using namespace std;

// A class representing a Binary Indexed Tree (BIT), also known as Fenwick Tree.
struct BIT
{
    int n;                  // The size of the array for which the tree is constructed
    vector<long long> tree; // The internal data structure where the tree is stored

    // Constructor to initialize the BIT with a given size
    BIT(int n) : n(n), tree(n + 1, 0) {}

    // Function to add a value to an element (1-based index) and update the tree
    void add(int i, long long delta)
    {
        // Increment the index by 1 to change from 0-based to 1-based indexing
        for (++i; i <= n; i += i & -i) // Traverse all ancestors of i
        {
            tree[i] += delta; // Update each ancestor's value
        }
    }

    // Function to calculate the prefix sum from index 1 to i (1-based index)
    long long sum(int i)
    {
        long long sum = 0; // Initialize the sum
        // Traverse the tree from i to 0
        for (; i > 0; i -= i & -i) // Move from child to parent
        {
            sum += tree[i]; // Add each ancestor's value to the sum
        }
        return sum; // Return the total sum
    }
};

int main()
{
    ios::sync_with_stdio(false); // Speed up I/O
    cin.tie(NULL);               // Prevent flushing of cout before cin is done

    int N, Q;      // N = Number of elements, Q = Number of queries
    cin >> N >> Q; // Read the number of elements and queries

    BIT bit(N); // Create a Binary Indexed Tree of size N

    for (int i = 0; i < Q; i++) // Loop through all queries
    {
        char c;   // Variable to store the query type
        cin >> c; // Read the query type

        // Handle the query based on its type
        if (c == '?')
        {
            int idx;    // Index for the query
            cin >> idx; // Read the index for the sum query
            // Output the prefix sum up to the given index
            cout << bit.sum(idx) << "\n";
        }
        else if (c == '+')
        {
            int idx;             // Index for the update
            long long delta;     // Value to add
            cin >> idx >> delta; // Read the index and value for the update query
            bit.add(idx, delta); // Update the BIT with the given value at the given index
        }
    }
    return 0;
}
