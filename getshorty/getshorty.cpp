#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <iomanip>

using namespace std;
typedef pair<double, int> pdi; // Pair of (distance, node)
constexpr char nl = '\n';

// Set to true to enable debug output.
constexpr bool VERBOSE = false;

struct Graph
{
    vector<vector<pdi>> adj; // Adjacency list.
    int nNodes{0};
    int nEdges{0};
};

pair<vector<double>, vector<int>> shortestPath(Graph G)
{
    // dist holds the shortest distance from the start node to every other node. Initialized to INT_MAX.
    vector<double> dist(G.nNodes, 0.0);
    vector<bool> visited(G.nNodes, false);

    // parents holds the parent node of each node in the shortest path from the start node.
    vector<int> parents(G.nNodes, -1);

    // Reading the edges and their weights into the adjacency list.
    for (int i = 0; i < G.nEdges; i++)
    {
        int fromNode, toNode;
        double weight;
        cin >> fromNode >> toNode >> weight;
        if (VERBOSE)
            cout << "fromNode: " << fromNode << " toNode: " << toNode << " weight: " << weight << nl;
        // Creating a directed edge from fromNode to toNode with the given weight.
        G.adj[fromNode].push_back({weight, toNode});
        G.adj[toNode].push_back({weight, fromNode}); // Adding the reverse edge for undirected graphs.
    }

    // Priority queue to efficiently fetch the next node to process based on the shortest distance.
    priority_queue<pdi> pq;
    // Distance to the start node is 0.
    dist[0] = 1.0;
    // Add the start node to the priority queue.
    pq.push({1.0, 0});

    // Process nodes until there are no more nodes in the queue.
    while (!pq.empty())
    {
        // Get the node with the shortest distance from the queue.
        double currentDist = pq.top().first;
        int currentNode = pq.top().second;
        pq.pop();

        // Skip if a shorter path to this node has already been found.
        if (currentDist > dist[currentNode])
            continue;

        if (visited[currentNode])
            continue;

        visited[currentNode] = true;

        // Check all adjacent nodes.
        for (auto edge : G.adj[currentNode])
        {
            double nextDist = edge.first;
            int nextNode = edge.second;

            // Update the distance to the adjacent node if a shorter path is found.
            if (dist[nextNode] < dist[currentNode] * nextDist)
            {
                dist[nextNode] = dist[currentNode] * nextDist;
                pq.push({dist[nextNode], nextNode});
            }
        }
    }

    if (VERBOSE)
    {
        cout << "Shortest distances from node 0 to all other nodes: " << nl;
        for (int i = 0; i < G.nNodes; i++)
        {
            cout << "Node " << i << " has distance: " << dist[i] << nl;
        }
    }

    return {dist, parents};
}

void printGraph(Graph G)
{
    for (int i = 0; i < G.nNodes; i++)
    {
        cout << "Node " << i << " has neighbors: ";
        for (auto neighbor : G.adj[i])
        {
            cout << neighbor.second << " ";
        }
        cout << nl;
    }
}

int main()
{
    ios::sync_with_stdio(false); // Speeds up input/output operations.
    cin.tie(NULL);               // Unties cin from cout - more input/output efficiency.
    cout.tie(NULL);

    // Continuously read test cases until a line with four zeros is encountered.
    while (true)
    {
        int nNodes, nEdges;
        cin >> nNodes >> nEdges;
        // Break the loop if a line with two zeros is encountered.
        if (nNodes == 0 && nEdges == 0)
            break;

        if (VERBOSE)
            cout << "nNodes: " << nNodes << " nEdges: " << nEdges << nl;

        // adj is an adjacency list, where each node has a list of its neighbors and the weight of the edge to them.
        vector<vector<pdi>> adj(nNodes);

        Graph G = {adj, nNodes, nEdges};

        vector<double> outDist = shortestPath(G).first;
        // vector<int> outParents = shortestPathDistances(G, startNode).second;

        // Handling the queries - output the shortest distance to each requested node.
        // If the distance is INT_MAX, the node is unreachable.
        cout << setprecision(4) << fixed << outDist[nNodes - 1] << nl; // Output the shortest distance.

        cout << nl; // New line for readability between test cases.
    }

    return 0;
}