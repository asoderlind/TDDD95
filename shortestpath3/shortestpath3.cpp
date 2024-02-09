/** TDDD95: Lab 2 - shortestpath3
 * Author: Axel Söderlind
 * Date:   2024-02-09
 * This problem is about finding
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

constexpr char nl = '\n'; // newline shortcut
bool DEBUG = false;       // flag for debugging

struct Edge
{
    int dest, weight;
};

struct Graph
{
    vector<vector<Edge>> adj; // Adjacency list
    int nNodes{0};
    int nEdges{0};
    int nQueries{0};
};

// Recursive function to mark all nodes reachable from
// a given node as affected by a negative cycle
void markReachableNodes(Graph &G, int start, vector<bool> &inNegativeCycle)
{
    inNegativeCycle[start] = true;
    for (Edge edge : G.adj[start])
    {
        if (!inNegativeCycle[edge.dest])
        {
            markReachableNodes(G, edge.dest, inNegativeCycle);
        }
    }
}

// Bellman-Ford algorithm to find shortest paths and detect negative cycles
pair<vector<int>, vector<bool>> BellmanFord(Graph &G, int startNode)
{
    vector<int> dist(G.nNodes, INT_MAX);
    vector<int> parents(G.nNodes, -1);
    vector<bool> inNegativeCycle(G.nNodes, false);

    dist[startNode] = 0;

    // Step 2: Relax all edges |nNodes| - 1 times
    for (int i = 1; i <= G.nNodes - 1; i++)
    {
        for (int j = 0; j < G.nNodes; j++)
        {
            int currentNode = j;
            for (Edge edge : G.adj[currentNode])
            {
                int v = edge.dest;
                int weight = edge.weight;
                if (dist[currentNode] != INT_MAX && dist[currentNode] + weight < dist[v])
                {
                    dist[v] = dist[currentNode] + weight;
                    parents[v] = currentNode;
                }
            }
        }
    }

    // Step 3: check for negative-weight cycles
    for (int j = 0; j < G.nNodes; j++)
    {
        int currentNode = j;
        for (Edge edge : G.adj[currentNode])
        {
            int weight = edge.weight;
            if (dist[currentNode] != INT_MAX && dist[currentNode] + weight < dist[edge.dest])
            {
                markReachableNodes(G, edge.dest, inNegativeCycle);
            }
        }
    }

    return {dist, inNegativeCycle};
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    // read input
    // Continuously read test cases until a line with four zeros is encountered.
    while (true)
    {
        int nNodes, nEdges, nQueries, startNode;
        cin >> nNodes >> nEdges >> nQueries >> startNode;
        // Break the loop if a line with four zeros is encountered.
        if (nNodes == 0 && nEdges == 0 && nQueries == 0 && startNode == 0)
            break;

        if (DEBUG)
            cout << "nNodes: " << nNodes << " nEdges: " << nEdges << " nQueries: " << nQueries << " startNode: " << startNode << nl;

        vector<vector<Edge>> adj(nNodes);

        Graph G = {adj, nNodes, nEdges, nQueries};

        // Step 1: Initialize distances from start to all other vertices as INT_MAX
        // Reading the edges and their weights into the adjacency list.
        for (int i = 0; i < G.nEdges; i++)
        {
            int src, dest, weight;
            cin >> src >> dest >> weight;
            // Creating a directed edge from fromNode to toNode with the given weight.
            G.adj[src].push_back({dest, weight});

            if (DEBUG)
            {
                cout << "Edge from " << src << " to " << dest << " with weight: " << weight << nl;
            }
        }

        // adj is an adjacency list, where each node has a list of its neighbors and the weight of the edge to them.

        pair<vector<int>, vector<bool>> result = BellmanFord(G, startNode);
        vector<int> outDist = result.first;
        vector<bool> inNegativeCycle = result.second;

        // Handling the queries - output the shortest distance to each requested node.
        for (int i = 0; i < G.nQueries; i++)
        {
            int queryNode;
            cin >> queryNode;
            // If the distance is INT_MAX, the node is unreachable.
            if (inNegativeCycle[queryNode])
                cout << "-Infinity" << nl;
            else if (outDist[queryNode] == INT_MAX)
                cout << "Impossible" << nl;
            else
                cout << outDist[queryNode] << nl; // Output the shortest distance.
        }

        cout << nl; // New line for readability between test cases.
    }

    return 0;
}