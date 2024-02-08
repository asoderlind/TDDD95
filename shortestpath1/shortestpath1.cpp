/** TDDD95: Lab 2 - shortestpath1
 * Author: Axel Söderlind
 * Date:   2024-01-31
 * This problem is about finding the shortest path
 * between two nodes in a graph (if possible)
 * and then returning that distance. To solve it
 * we use Djikstras algorithm with a priority queue.
 *
 * Time complexity: O((n{nodes} + n{edges})*log(n{nodes}))
 * Space: O(n{Nodes} + n{Edges})
 */
#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;
typedef pair<int, int> pii; // Pair of (distance, node)
constexpr char nl = '\n';

struct Graph
{
    vector<vector<pii>> adj;
    int nNodes{0};
    int nEdges{0};
    int nQueries{0};
};

pair<vector<int>, vector<int>> shortestPathDistances(Graph G, int startNode)
{
    // dist holds the shortest distance from the start node to every other node. Initialized to INT_MAX.
    vector<int> dist(G.nNodes, INT_MAX);

    // parents holds the parent node of each node in the shortest path from the start node.
    vector<int> parents(G.nNodes, -1);

    // Reading the edges and their weights into the adjacency list.
    for (int i = 0; i < G.nEdges; i++)
    {
        int fromNode, toNode, weight;
        cin >> fromNode >> toNode >> weight;
        // Creating a directed edge from fromNode to toNode with the given weight.
        G.adj[fromNode].push_back({weight, toNode});
    }

    // Priority queue to efficiently fetch the next node to process based on the shortest distance.
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    // Distance to the start node is 0.
    dist[startNode] = 0;
    // Add the start node to the priority queue.
    pq.push({0, startNode});

    // Process nodes until there are no more nodes in the queue.
    while (!pq.empty())
    {
        // Get the node with the shortest distance from the queue.
        int currentDist = pq.top().first;
        int currentNode = pq.top().second;
        pq.pop();

        // Skip if a shorter path to this node has already been found.
        if (currentDist > dist[currentNode])
            continue;

        // Check all adjacent nodes.
        for (auto edge : G.adj[currentNode])
        {
            int nextNode = edge.second;
            int nextDist = edge.first;

            // Update the distance to the adjacent node if a shorter path is found.
            if (dist[currentNode] + nextDist < dist[nextNode])
            {
                dist[nextNode] = dist[currentNode] + nextDist;
                parents[nextNode] = currentNode; // Update the parent of the adjacent node.
                // Add the updated node to the priority queue.
                pq.push({dist[nextNode], nextNode});
            }
        }
    }

    return {dist, parents};
}

int main()
{
    ios::sync_with_stdio(false); // Speeds up input/output operations.
    cin.tie(NULL);               // Unties cin from cout - more input/output efficiency.
    cout.tie(NULL);

    // Continuously read test cases until a line with four zeros is encountered.
    while (true)
    {
        int nNodes, nEdges, nQueries, startNode;
        cin >> nNodes >> nEdges >> nQueries >> startNode;
        // Break the loop if a line with four zeros is encountered.
        if (nNodes == 0 && nEdges == 0 && nQueries == 0 && startNode == 0)
            break;

        // adj is an adjacency list, where each node has a list of its neighbors and the weight of the edge to them.
        vector<vector<pii>> adj(nNodes);

        Graph G = {adj, nNodes, nEdges, nQueries};

        vector<int> outDist = shortestPathDistances(G, startNode).first;
        // vector<int> outParents = shortestPathDistances(G, startNode).second;
        // Handling the queries - output the shortest distance to each requested node.
        for (int i = 0; i < G.nQueries; i++)
        {
            int queryNode;
            cin >> queryNode;
            // If the distance is INT_MAX, the node is unreachable.
            if (outDist[queryNode] == INT_MAX)
                cout << "Impossible" << nl;
            else
                cout << outDist[queryNode] << nl; // Output the shortest distance.
        }

        cout << nl; // New line for readability between test cases.
    }

    return 0;
}