/** TDDD95: Lab 2 - maxflow
 * Author: Axel Söderlind
 * Date:   2024-03-13
 * This problem is about finding the maximum flow in a graph.
 * To solve it we use the Ford-Fulkerson algorithm. We start by
 * reading the input and then we create a graph and run the
 * algorithm. We then print the result.
 *
 * Time complexity: O(max_flow * n{edges})
 * Space: O(n{vertices})
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <climits>
#include <map>

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
    vector<vector<int>> adj;         // Adjacency matrix
    vector<vector<int>> capacity;    // Capacity matrix
    vector<vector<int>> flow;        // Flow matrix
    vector<vector<bool>> directions; // Edge directions matrix
};

graph initGraph(int n)
{
    graph G;
    G.numNodes = n;
    G.adj.resize(n, vector<int>());
    G.capacity.resize(n, vector<int>(n, 0));
    G.flow.resize(n, vector<int>(n, 0));
    G.directions.resize(n, vector<bool>(n, false));
    return G;
}

/// @brief Find a path from s to t in the graph using BFS.
/// @param G The graph to search in.
/// @param source The source node.
/// @param sink The sink node.
/// @param parent The parent vector to store the path.
/// @return
int bfs(graph &G, int source, int sink, vector<int> &parent)
{
    fill(parent.begin(), parent.end(), -1);
    parent[source] = -2;     // Mark the source node as visited
    queue<pair<int, int>> q; // Queue to hold the nodes to visit
    q.push({source, INT_MAX});

    while (!q.empty()) // Standard BFS loop
    {
        int currentNode = q.front().first;
        int currentFlow = q.front().second;
        q.pop();

        for (int nextNode : G.adj[currentNode])
        {
            if (parent[nextNode] == -1 && G.capacity[currentNode][nextNode] > 0)
            {
                parent[nextNode] = currentNode;
                // We send the minimum flow we have seen so far up to this node
                int newFlow = min(currentFlow, G.capacity[currentNode][nextNode]);
                if (nextNode == sink)
                    return newFlow;
                q.push({nextNode, newFlow});
            }
        }
    }

    return 0;
}

/// @brief Implement the Ford-Fulkerson algorithm to find the maximum flow in a graph.
/// @param G The graph to find the maximum flow in.
/// @param source The source node.
/// @param sink The sink node.
/// @return A graph representing the flow network and the maximum flow.
pair<graph, int> fordFulkerson(graph &G, int source, int sink)
{
    vector<int> parent(G.numNodes); // This array is filled by BFS and to store path

    int maxFlow = 0; // There is no flow to the sink initially
    int newFlow;     // placeholder for the new flow

    // Augment the flow while there is path from source to sink
    while ((newFlow = bfs(G, source, sink, parent)))
    {
        maxFlow += newFlow; // add minimum flow to max_flow
        int current = sink;
        while (current != source) // update capacities along the path
        {
            int previous = parent[current];
            G.flow[previous][current] += newFlow;
            G.flow[current][previous] -= newFlow;
            G.capacity[previous][current] -= newFlow;
            G.capacity[current][previous] += newFlow;
            current = previous;
        }
    }

    if (DEBUG)
    {
        std::cout << "Flow matrix:" << nl;
        for (int i = 0; i < G.numNodes; i++)
        {
            for (int j = 0; j < G.numNodes; j++)
            {
                std::cout << G.flow[i][j] << " ";
            }
            std::cout << nl;
        }
    }

    // Return updated graph and max flow
    return {G, maxFlow};
}

/// @brief  Print the edges in the solution graph.
/// @param G The graph to print the edges from.
void printSolutionEdges(graph G)
{
    map<pair<int, int>, int> edges;
    for (int i = 0; i < (int)G.adj.size(); i++)
    {
        for (int j = 0; j < (int)G.adj[i].size(); j++)
        {
            int nextNode = G.adj[i][j];
            if (G.flow[i][nextNode] > 0 && G.directions[i][nextNode])
            {
                edges[{i, nextNode}] = G.flow[i][nextNode];
            }
        }
    }
    cout << edges.size() << nl; // Print the number of edges

    // Print the edges
    for (auto edge = edges.begin(); edge != edges.end(); edge++)
    {
        int from = edge->first.first;
        int to = edge->first.second;
        int flow = edge->second;
        cout << from << " " << to << " " << flow << nl;
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    if (DEBUG)
        std::cout << "Debugging" << nl;

    // read input
    int numNodes, numEdges, source, sink;
    cin >> numNodes >> numEdges >> source >> sink;

    graph G = initGraph(numNodes);

    rep(i, 0, numEdges)
    {
        int from, to, capacity; // from, to, capacity
        cin >> from >> to >> capacity;
        G.directions[from][to] = true;
        G.adj[from].push_back(to);
        G.adj[to].push_back(from);
        G.capacity[from][to] += capacity;
    }

    auto [newG, maxFlow] = fordFulkerson(G, source, sink);
    cout << numNodes << " " << maxFlow << " ";
    printSolutionEdges(newG);

    return 0;
}