/** TDDD95: Lab 2 - minspantree
 * Author: Axel Söderlind
 * Date:   2024-02-16
 * This problem is about finding the minimum spanning tree of a graph.
 * To solve it we use Kruskal's algorithm.
 *
 * Time complexity: O(E * logV)
 * Space: O(E + V) where E is the number of edges and V
 * is the number of vertices.
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef long double ld;

bool DEBUG = false;

#define rep(i, a, b) for (int i = a; i < b; ++i)

constexpr char nl = '\n';
constexpr ll INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 998244353;
constexpr ld EPS = 1e-9L;

// ------------------------------------------- //

struct Edge
{
    int from, to, weight;
};

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

vector<Edge> Kruskal(vector<Edge> &edges, int n)
{
    // Stores the edges of the minimum spanning tree.
    vector<Edge> mst;

    // Sort the edges by weight
    sort(edges.begin(), edges.end(), [](Edge a, Edge b)
         { return a.weight < b.weight; });

    // Create a DisjointSet with n nodes.
    DisjointSet ds(n);

    // Iterate through the edges and add them to the minimum spanning tree if they don't create a cycle.
    for (Edge e : edges)
    {
        int parentFrom = ds.find(e.from);
        int parentTo = ds.find(e.to);
        if (parentFrom != parentTo)
        {
            ds.union_sets(e.from, e.to);
            mst.push_back(e);
        }
    }

    return mst;
}

void printMST(vector<Edge> &mst)
{
    // Calculate and print the sum of weights
    int sum_weight = 0;
    for (Edge &e : mst)
    {
        sum_weight += e.weight;
    }
    cout << sum_weight << nl;

    // First, ensure x < y for each edge
    for (Edge &e : mst)
    {
        if (e.from > e.to)
        {
            swap(e.from, e.to);
        }
    }

    // Then, sort the edges lexicographically
    sort(mst.begin(), mst.end(), [](const Edge &a, const Edge &b)
         {
        if (a.from != b.from)
            return a.from < b.from;
        return a.to < b.to; });

    // Print the edges
    for (Edge &e : mst)
    {
        cout << e.from << " " << e.to << nl;
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    // Continuously read test cases until a line with four zeros is encountered.
    while (true)
    {
        int numNodes, numEdges;
        cin >> numNodes >> numEdges;

        vector<Edge> edges(numEdges);

        // Break the loop if a line with four zeros is encountered.
        if (numNodes == 0 && numEdges == 0)
            break;

        // Read the edges
        rep(i, 0, numEdges)
        {
            int from, to, weight;
            cin >> from >> to >> weight;
            edges[i] = {from, to, weight};
        }

        // run Kruskal's algorithm
        vector<Edge> mst = Kruskal(edges, numNodes);

        if (mst.size() == numNodes - 1)
        {
            printMST(mst);
        }
        else
        {
            cout << "impossible" << nl;
        }
    }

    return 0;
}