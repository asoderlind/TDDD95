/** TDDD95: Lab X - <name>
 * Author: Axel Söderlind
 * Date:   2024-01-22
 * This problem is about ...
 */
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;
typedef long double ld;

#define rep(i, a, b) for (int i = a; i < b; ++i)

bool DEBUG = true;

constexpr char nl = '\n';
constexpr ll INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 998244353;
constexpr ld EPS = 1e-9L;

// ------------------------------------------- //

struct Edge {
  int from, to;
  float weight;
};

class DisjointSet {
  // Stores the parent of each element. Initially, each element is its own parent.
  vector<int> parent;
  // Stores the rank (approximate depth) of each set. Used in union_sets to optimize merging.
  vector<int> rank;

 public:
  // Constructor: initializes the data structure with n elements, each in its own set.
  DisjointSet(int n) : parent(n), rank(n, 0) {
    for (int i = 0; i < n; ++i) parent[i] = i;
  }

  // Finds the representative (root) of the set that contains element x.
  // Implements path compression to optimize future queries.
  int find(int x) {
    if (parent[x] != x) parent[x] = find(parent[x]);
    return parent[x];
  }

  // Merges the sets containing elements a and b.
  // Uses the rank to attach the smaller tree to the
  // root of the larger tree to maintain balance.
  void union_sets(int a, int b) {
    a = find(a);
    b = find(b);
    if (a != b) {
      if (rank[a] < rank[b]) swap(a, b);
      parent[b] = a;
      if (rank[a] == rank[b]) rank[a]++;
    }
  }

  // Checks if elements a and b belong to the same set.
  bool same(int a, int b) { return find(a) == find(b); }
};

vector<Edge> Kruskal(vector<Edge> &edges, int n) {
  // Stores the edges of the minimum spanning tree.
  vector<Edge> mst;

  // Sort the edges by weight
  sort(edges.begin(), edges.end(), [](Edge a, Edge b) { return a.weight < b.weight; });

  // Create a DisjointSet with n nodes.
  DisjointSet ds(n);

  // Iterate through the edges and add them to the minimum spanning tree if they don't create a cycle.
  for (Edge e : edges) {
    int parentFrom = ds.find(e.from);
    int parentTo = ds.find(e.to);
    if (parentFrom != parentTo) {
      ds.union_sets(e.from, e.to);
      mst.push_back(e);
    }
  }

  return mst;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(NULL);
  std::cout.tie(NULL);
  // set precision
  cout.precision(17);

  // read input
  int numTestCases;
  cin >> numTestCases;
  while (numTestCases--) {
    vector<Edge> edges;
    int numIslands;
    cin >> numIslands;
    vector<pair<float, float>> islands(numIslands);
    // load islands
    for (int i = 0; i < numIslands; ++i) {
      cin >> islands[i].first >> islands[i].second;
    }
    // populate edges
    for (int i = 0; i < numIslands; ++i) {
      for (int j = i + 1; j < numIslands; ++j) {
        Edge e;
        e.from = i;
        e.to = j;
        e.weight = sqrt(pow(islands[i].first - islands[j].first, 2) + pow(islands[i].second - islands[j].second, 2));
        edges.push_back(e);
      }
    }
    // calculate minimum spanning tree
    vector<Edge> mst = Kruskal(edges, numIslands);
    float minTotalDistance = 0.0;
    // Calculate and print the sum of weights
    for (Edge &e : mst) {
      minTotalDistance += e.weight;
    }
    cout << minTotalDistance << nl;
  }

  return 0;
}