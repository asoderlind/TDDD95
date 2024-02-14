/** TDDD95: Lab 2 - shortestpath2
 * Author: Axel Söderlind
 * Date:   2024-02-09
 * This problem is about finding the shortest time
 * between two nodes in a graph (if possible) where
 * the nodes are only available at certain times
 * and intervals, that must be taken into account.
 * To solve it we use Djikstras algorithm with a priority queue.
 *
 * Time complexity: O(n{edges}*log(n{edges}))
 * Space: O(n{Nodes} + n{Edges})
 */
#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;
constexpr char nl = '\n';

bool DEBUG = false;

struct Edge
{
    int toNode;
    int t0;
    int period;
    int time;
};

struct State
{
    int currentNode;
    int currentTime;
};

struct CompareState
{
    bool operator()(State const &s1, State const &s2)
    {
        return s1.currentTime > s2.currentTime;
    }
};

struct Graph
{
    vector<vector<Edge>> adj; // Adjacency list
    int nNodes{0};
    int nEdges{0};
    int nQueries{0};
};

pair<vector<int>, vector<int>> shortestPath(Graph G, int startNode)
{
    // dist holds the shortest time from the start node to every other node. Initialized to INT_MAX.
    vector<int> times(G.nNodes, INT_MAX);

    // parents holds the parent node of each node in the shortest path from the start node.
    vector<int> parents(G.nNodes, -1);

    // Reading the edges and their weights into the adjacency list.
    for (int i = 0; i < G.nEdges; i++)
    {
        int fromNode, toNode, t0, period, time;
        cin >> fromNode >> toNode >> t0 >> period >> time;
        // Creating a directed edge from fromNode to toNode with the given weight.
        G.adj[fromNode].push_back({toNode, t0, period, time});

        if (DEBUG)
        {
            cout << "Edge from " << fromNode << " to " << toNode << " with t0: " << t0 << " period: " << period << " time: " << time << nl;
        }
    }

    // Priority queue to efficiently fetch the next node to process based on the shortest times.
    priority_queue<State, vector<State>, CompareState> pq;

    // Time to the start node is 0.
    times[startNode] = 0;

    // Add the start node to the priority queue.
    pq.push({startNode, 0});

    // Process nodes until there are no more nodes in the queue.
    while (!pq.empty())
    {
        // Get the node with the shortest time from the priority queue
        int currentNode = pq.top().currentNode;
        int currentTime = pq.top().currentTime;
        pq.pop();

        // Skip if a shorter time to this node has already been found.
        if (currentTime > times[currentNode])
            continue;

        // Check all adjacent nodes.
        for (Edge edge : G.adj[currentNode])
        {
            int nextNode = edge.toNode;
            int waitTime = 0;
            int edgeAvailableTime = edge.t0;

            // If the edge is periodic, find the next time it is available.
            if (edge.period > 0)
            {
                if (currentTime > edgeAvailableTime)
                {
                    int periodsPassed = (currentTime - edgeAvailableTime + edge.period - 1) / edge.period;
                    edgeAvailableTime += periodsPassed * edge.period;
                }
                waitTime = max(0, edgeAvailableTime - currentTime);
            }
            // If the edge is not periodic and the time is in the past, wait until it is available.
            else if (edge.period == 0 && currentTime < edgeAvailableTime)
            {
                waitTime = edgeAvailableTime - currentTime;
                if (DEBUG)
                {
                    cout << "Edge from " << currentNode << " to " << nextNode << " is not periodic and the current time is past t0." << nl;
                }
            }
            // If the edge is not periodic and the current time is past t0, the edge cannot be used.
            else if (edge.period == 0 && currentTime > edgeAvailableTime)
            {
                continue;
            }

            // Calculate the time it takes to travel to the next node.
            int arrivalTime = currentTime + waitTime + edge.time;

            // If the arrival time is shorter than the current time to the next node, update the time and parent.
            if (arrivalTime < times[nextNode])
            {
                times[nextNode] = arrivalTime;
                parents[nextNode] = currentNode;
                pq.push({nextNode, arrivalTime});
            }
        }
    }
    return {times, parents};
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
        vector<vector<Edge>> adj(nNodes);

        Graph G = {adj, nNodes, nEdges, nQueries};

        vector<int> outDist = shortestPath(G, startNode).first;

        Graph G = {adj, nNodes, nEdges, nQueries};

        vector<int> outDist = shortestPath(G, startNode).first;

        // Handling the queries - output the shortest times to each requested node.
        for (int i = 0; i < G.nQueries; i++)
        {
            int queryNode;
            cin >> queryNode;
            // If the time is INT_MAX, the node is unreachable.
            if (outDist[queryNode] == INT_MAX)
                cout << "Impossible" << nl; // Output "Impossible".
            else
                cout << outDist[queryNode] << nl; // Output the shortest time.
        }

        cout << nl; // New line for readability between test cases.
    }

    return 0;
}