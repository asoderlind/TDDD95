/** TDDD95: Lab 2 - allpairspath
 * Author: Axel Söderlind
 * Date:   2024-02-16
 * This problem is about finding the shortest path
 * between two nodes in a graph (if possible) where
 * the graph may contain negative cycles. To solve it
 * we use the Bellman-Ford algorithm.
 *
 * Time complexity: O(n^3) where n is the number of nodes.
 * Space: O(n^2) where n is the number of nodes.
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

#define rep(i, a, b) for (int i = a; i < b; ++i)

constexpr char nl = '\n'; // newline shortcut
bool DEBUG = false;       // flag for debugging

struct Graph
{
    int numNodes{0};
    int numEdges{0};
    vector<vector<int>> distances;
};

vector<vector<int>> FloydWarshall(Graph &G)
{
    int n = G.numNodes;
    int m = G.numEdges;
    vector<vector<int>> d = G.distances;

    rep(i, 0, n) d[i][i] = min(d[i][i], 0); // make sure self-loops are set to max 0

    // Floyd-Warshall algorithm which finds the shortest path between all pairs of nodes.
    // The algorithm works by iteratively updating the shortest path between all pairs of nodes.
    rep(k, 0, n) rep(i, 0, n) rep(j, 0, n) if (d[i][j] > (d[i][k] + d[k][j]) && d[i][k] != INT_MAX && d[k][j] != INT_MAX)
    {
        d[i][j] = d[i][k] + d[k][j];
    }

    // Detecting negative cycles and setting the distance to -INT_MAX for
    // all nodes that are part of a negative cycle.
    rep(k, 0, n) rep(i, 0, n) rep(j, 0, n) if (d[k][k] < 0 && d[i][k] < INT_MAX && d[k][j] < INT_MAX)
    {
        d[i][j] = -INT_MAX;
    }

    return d;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    // Continuously read test cases until a line with four zeros is encountered.
    while (true)
    {
        int numNodes, numEdges, numQueries;
        cin >> numNodes >> numEdges >> numQueries;
        // Break the loop if a line with four zeros is encountered.
        if (numNodes == 0 && numEdges == 0 && numQueries == 0)
            break;

        if (DEBUG)
            cout << "nNodes: " << numNodes << " nEdges: " << numEdges << " nQueries: " << numQueries << " startNode: " << nl;

        // initialize distances to INT_MAX
        vector<vector<int>> distances(numNodes, vector<int>(numNodes, INT_MAX));

        Graph graph = {numNodes, numEdges, distances};

        // Read the edges and their weights.
        for (int i = 0; i < graph.numEdges; i++)
        {
            int src, dest, weight;
            cin >> src >> dest >> weight;
            graph.distances[src][dest] = min(graph.distances[src][dest], weight);
            if (DEBUG)
            {
                cout << "Edge from " << src << " to " << dest << " with weight: " << weight << nl;
            }
        }

        auto outDist = FloydWarshall(graph);

        // Handling the queries - output the shortest distance to each requested node.
        for (int i = 0; i < numQueries; i++)
        {
            int queryFromNode, queryToNode;
            cin >> queryFromNode >> queryToNode;
            // If the distance is INT_MAX, the node is unreachable.
            if (outDist[queryFromNode][queryToNode] == INT_MAX)
                cout << "Impossible" << nl;
            // If the distance is -INT_MAX, the node is part of a negative cycle.
            else if (outDist[queryFromNode][queryToNode] == -INT_MAX)
                cout << "-Infinity" << nl;
            else
                cout << outDist[queryFromNode][queryToNode] << nl;
        }

        cout << nl; // New line for readability between test cases.
    }

    return 0;
}