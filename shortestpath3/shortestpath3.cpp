/** TDDD95: Lab 2 - shortestpath3
 * Author: Axel Söderlind
 * Date:   2024-02-09
 * This problem is about finding the shortest path
 * between two nodes in a graph (if possible) where
 * the graph may contain negative cycles. To solve it
 * we use the Bellman-Ford algorithm.
 *
 * Time complexity: O(n{nodes}*n{edges})
 * Space: O(n{Nodes} + n{Edges})
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
    vector<vector<Edge>> adjList; // Adjacency list
    int numNodes{0};
    int numEdges{0};
    int numQueries{0};
};

// Recursive function to mark all nodes reachable from
// a given node as affected by a negative cycle
void markReachableNodes(Graph &G, int start, vector<bool> &inNegativeCycle)
{
    inNegativeCycle[start] = true;
    for (Edge edge : G.adjList[start])
    {
        if (!inNegativeCycle[edge.dest])
        {
            markReachableNodes(G, edge.dest, inNegativeCycle);
        }
    }
}

// Bellman-Ford algorithm to find shortest paths and detect negative cycles
pair<vector<int>, vector<bool>> BellmanFord(Graph &graph, int startNode)
{
    vector<int> distances(graph.numNodes, INT_MAX);         // Shortest distances from startNode to all other nodes
    vector<int> predecessors(graph.numNodes, -1);           // Predecessors of each node in the path
    vector<bool> affectedByNegCycle(graph.numNodes, false); // Flags to indicate if a node is affected by a negative cycle

    distances[startNode] = 0; // Distance from startNode to itself is 0

    // Relax all edges |V| - 1 times (V is the number of vertices in the graph)
    for (int i = 1; i <= graph.numNodes - 1; i++)
    {
        for (int currentNode = 0; currentNode < graph.numNodes; currentNode++)
        {
            for (const Edge &edge : graph.adjList[currentNode])
            {
                int v = edge.dest;
                int weight = edge.weight;
                if (distances[currentNode] != INT_MAX && distances[currentNode] + weight < distances[v])
                {
                    distances[v] = distances[currentNode] + weight;
                    predecessors[v] = currentNode;
                }
            }
        }
    }

    // Check for negative-weight cycles
    for (int currentNode = 0; currentNode < graph.numNodes; currentNode++)
    {
        for (const Edge &edge : graph.adjList[currentNode])
        {
            if (distances[currentNode] != INT_MAX && distances[currentNode] + edge.weight < distances[edge.dest])
            {
                markReachableNodes(graph, edge.dest, affectedByNegCycle);
            }
        }
    }

    return {distances, affectedByNegCycle};
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

        vector<vector<Edge>> adjList(nNodes);
        Graph graph = {adjList, nNodes, nEdges, nQueries};

        for (int i = 0; i < graph.numEdges; i++)
        {
            int src, dest, weight;
            cin >> src >> dest >> weight;
            // Creating a directed edge from fromNode to toNode with the given weight.
            graph.adjList[src].push_back({dest, weight});

            if (DEBUG)
            {
                cout << "Edge from " << src << " to " << dest << " with weight: " << weight << nl;
            }
        }

        pair<vector<int>, vector<bool>> result = BellmanFord(graph, startNode);
        vector<int> outDist = result.first;
        vector<bool> inNegativeCycle = result.second;

        // Handling the queries - output the shortest distance to each requested node.
        for (int i = 0; i < graph.numQueries; i++)
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