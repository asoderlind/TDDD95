/** TDDD95: Lab X - <name>
 * Author: Axel Söderlind
 * Date:   2024-01-22
 * This problem is about ...
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

typedef long long ll;
typedef long double ld;

#define rep(i, a, b) for (int i = a; i < b; ++i)

bool DEBUG = false;

constexpr char nl = '\n';
constexpr ll INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 998244353;
constexpr ld EPS = 1e-9L;

// ------------------------------------------- //

struct graph
{
    int numNodes;
    int numEdges;
    vector<vector<int>> capacity;
    vector<vector<int>> residual;
};

/// @brief Find a path from s to t in the graph using BFS.
/// @param G The graph to search in.
/// @param s The source node.
/// @param t The sink node.
/// @param parent
/// @return
bool bfs(graph &G, int s, int t, int parent[])
{
    // Create a visited array and mark all vertices as not
    // visited
    bool visited[G.numNodes];
    memset(visited, 0, sizeof(visited));

    // Create a queue, enqueue source vertex and mark source
    // vertex as visited
    queue<int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    // Standard BFS Loop
    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (int v = 0; v < G.numNodes; v++)
        {
            if (visited[v] == false && G.residual[u][v] > 0)
            {
                // If we find a connection to the sink node,
                // then there is no point in BFS anymore we
                // just have to set its parent and can return
                // true
                if (v == t)
                {
                    parent[v] = u;
                    return true;
                }
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }

    // We didn't reach sink in BFS starting from source, so
    // return false
    return false;
}

void printGraph(graph G)
{
    cout << "Capacity matrix: \n";
    rep(i, 0, G.capacity.size())
    {
        rep(j, 0, G.capacity[i].size())
        {
            cout << G.capacity[i][j] << "\t";
        }
        cout << nl;
    }
    cout << "Residual matrix: \n";
    rep(i, 0, G.residual.size())
    {
        rep(j, 0, G.residual[i].size())
        {
            cout << G.residual[i][j] << "\t";
        }
        cout << nl;
    }
}

/// @brief Implement the Ford-Fulkerson algorithm to find the maximum flow in a graph.
/// @param G The graph to find the maximum flow in.
/// @param s The source node.
/// @param t The sink node.
/// @return A graph representing the flow network.
int fordFulkerson(graph &G, int s, int t)
{
    int u, v;

    // Create a residual graph and fill the residual graph
    // with given capacities in the original graph as
    // residual capacities in residual graph
    rep(u, 0, G.numNodes) rep(v, 0, G.numNodes) G.residual[u][v] = G.capacity[u][v];

    int parent[G.numNodes]; // This array is filled by BFS and to
                            // store path

    int max_flow = 0; // There is no flow initially

    // Augment the flow while there is path from source to
    // sink
    while (bfs(G, s, t, parent))
    {
        // Find minimum residual capacity of the edges along
        // the path filled by BFS. Or we can say find the
        // maximum flow through the path found.
        int path_flow = INT_MAX;
        for (v = t; v != s; v = parent[v])
        {
            u = parent[v];
            path_flow = min(path_flow, G.residual[u][v]);
        }

        // update residual capacities of the edges and
        // reverse edges along the path
        for (v = t; v != s; v = parent[v])
        {
            u = parent[v];
            G.residual[u][v] -= path_flow;
            G.residual[v][u] += path_flow;
        }

        // Add path flow to overall flow
        max_flow += path_flow;
    }

    // Return the overall flow
    return max_flow;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    if (DEBUG)
        std::cout << "Debugging" << nl;

    // read input
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    std::cout << n << " " << m << " " << s << " " << t << nl;

    graph G;
    G.numNodes = n;
    G.numEdges = m;
    G.capacity.resize(n, vector<int>(n, 0));
    G.residual.resize(n, vector<int>(n, 0));

    rep(i, 0, m)
    {
        int a, b, c; // from, to, capacity
        cin >> a >> b >> c;
        G.capacity[a][b] = c;
    }
    int flow_graph = fordFulkerson(G, s, t);

    if (DEBUG)
        printGraph(G);

    std::cout << "Max flow: " << flow_graph << nl;

    return 0;
}