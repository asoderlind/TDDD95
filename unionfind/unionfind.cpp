/** TDDD95: Lab 1 - unionfind
 * Author: Axel Söderlind
 * Date:   2024-01-25
 * This problem is about implementing a Union-Find data structure.
 * We use the DisjointSet class to solve this problem. We initialize
 * the data structure with n elements, each in its own set. We then
 * iterate through the queries and perform the appropriate operation
 * for each query.
 *
 * Complexity: O(logn) where n is the number of elements and q is the number of queries.
 * Space: O(n) where n is the number of elements.
 */
#include <vector>
#include <iostream>

using namespace std;

class DisjointSet
{
    // Stores the parent of each element. Initially, each element is its own parent.
    vector<int> parent;
    // Stores the rank (approximate depth) of each set. Used in union_sets to optimize merging.
    vector<int> rank;

public:
    // Constructor: initializes the data structure with n elements, each in its own set.
    DisjointSet(int n) : parent(n), rank(n, 0)
    {
        for (int i = 0; i < n; ++i)
            parent[i] = i;
    }

    // Finds the representative (root) of the set that contains element x.
    // Implements path compression to optimize future queries.
    int find(int x)
    {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    // Merges the sets containing elements a and b.
    // Uses the rank to attach the smaller tree to the
    // root of the larger tree to maintain balance.
    void union_sets(int a, int b)
    {
        a = find(a);
        b = find(b);
        if (a != b)
        {
            if (rank[a] < rank[b])
                swap(a, b);
            parent[b] = a;
            if (rank[a] == rank[b])
                rank[a]++;
        }
    }

    // Checks if elements a and b belong to the same set.
    bool same(int a, int b)
    {
        return find(a) == find(b);
    }
};

int main()
{
    std::ios::sync_with_stdio(false); // Disable sync with C to improve performance
    std::cin.tie(NULL);               // Disable flushing of cout before cin is performed

    int N, Q;

    // Read the number of elements (N) and the number of queries (Q)
    cin >> N >> Q;

    // Initialize DisjointSet with N elements
    DisjointSet ds(N);

    for (int i = 0; i < Q; i++)
    {
        char c;
        int a, b;

        // Read each query
        cin >> c >> a >> b;

        // Check if query is a union operation or a "same" check
        if (c == '?')
        {
            // If it's a "same" check, output whether a and b are in the same set
            if (ds.same(a, b))
                cout << "yes\n";
            else
                cout << "no\n";
        }
        else
        {
            // Perform union operation for a and b
            ds.union_sets(a, b);
        }
    }

    return 0;
}
