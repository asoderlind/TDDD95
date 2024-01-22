#include <vector>
#include <iostream>

using namespace std;

// The DisjointSet class represents a Union-Find data structure
// that keeps track of a set of elements partitioned into a number of disjoint (non-overlapping) subsets.
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
    // Uses the rank to attach the smaller tree to the root of the larger tree to maintain balance.
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
    // Disable synchronization with C I/O for performance improvement
    std::ios::sync_with_stdio(false);
    // Untie cin and cout for performance improvement
    std::cin.tie(NULL);

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
