/*
Philip Welin-Berger, phiwe030
Problem explanation:
Time complexity:
Space complexity:

Input:

 */

#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>
// for the love of god always use long long just to be on the safe side
using namespace std;

const int INF = 1000000000;
constexpr char nl = '\n';

void printVector(vector<int> v)
{
  for (int i = 0; i < int(v.size()); i++)
    std::cout << v[i] << " ";
  std::cout << nl;
}

// Function to restore the path from the start node to the given end node
// by following the previous node in the shortest path
vector<int> restore_path(int start, int to, vector<int> const &previous)
{
  vector<int> path;
  for (int v = to; v != start; v = previous[v])
    path.push_back(v);
  path.push_back(start);
  reverse(path.begin(), path.end());
  return path;
}

/*
Dijkstra's algorithm performs  n  iterations.

 */
void dijkstra(int start,
              vector<vector<tuple<int, int, int, int>>> &adjacencyList,
              vector<int> &time, vector<int> &previous)
{
  int nodes = adjacencyList.size();

  // Initialize time vector, a vector that will hold the time from the start
  // node to all other nodes time[n] = time from start to n
  time.assign(nodes, INF);
  time[start] = 0;
  // Initialise previous vector, a vector that will hold the previous node in
  // the shortest path
  previous.assign(nodes, -1);

  // Initialize visited vector
  vector<bool> visited(nodes, false);
  for (int n = 0; n < nodes; n++)
  {
    // Find the node (vertex) with the smallest time
    int vertex = -1;
    for (int i = 0; i < nodes; i++)
    {
      if (!visited[i] && (vertex == -1 || time[i] < time[vertex]))
      {
        vertex = i;
      }
    }

    // If the smallest distance among the unvisited nodes is infinity, then stop
    if (time[vertex] == INF)
      break;

    // Mark the node as visited
    visited[vertex] = true;

    // Update the distance value of the neighboring nodes
    // to, t0, P, traverseTime
    for (auto &neighbor : adjacencyList[vertex])
    {
      int to = get<0>(neighbor);
      int t0 = get<1>(neighbor);
      int P = get<2>(neighbor);
      int traverseTime = get<3>(neighbor);
      // Check if we're past the initial time and if periodic travel is not possible
      if (time[vertex] > t0 && P == 0)
        continue; // Skipping this node as travel is impossible (missed the only window at t0 with no repeats)

      int nextAvailableTime = time[vertex]; // Start from the current time at this vertex

      if (time[vertex] <= t0)
        // Can traverse at or immediately after t0
        nextAvailableTime = t0 + traverseTime;
      else if (P == 0)
        continue; // No future traversal windows
      else
      {
        // We're past t0 and periodic travel is possible
        int remainder = (time[vertex] - t0) % P;
        int waitTime = (remainder == 0) ? 0 : P - remainder;
        nextAvailableTime = time[vertex] + waitTime + traverseTime;
      }

      if (nextAvailableTime < time[to])
      {
        time[to] = nextAvailableTime;
        previous[to] = vertex;
      }
    }
  }
}

int main()
{
  std::ios::sync_with_stdio(false);
  std::cin.tie(NULL);
  int nodes, edges, queries, start;
  while (std::cin >> nodes >> edges >> queries >> start)
  {
    if (nodes == 0 && edges == 0 && queries == 0 && start == 0)
      break;

    // Initialize adjacency matrix
    // adjacencyList[from] = vector<{to, weight}>
    vector<vector<tuple<int, int, int, int>>> adjacencyList(nodes);
    for (int edge = 0; edge < edges; edge++)
    {
      int from, to, t0, P, traverseTime;
      std::cin >> from >> to >> t0 >> P >> traverseTime;
      adjacencyList[from].push_back({to, t0, P, traverseTime});
    }

    // Initialize time vector, a vector that will hold the time from the
    // start node to all other nodes time[n] = time from start to n
    vector<int> time;
    // Initialise previous vector, a vector that will hold the previous node in
    // the shortest path
    vector<int> previous;

    dijkstra(start, adjacencyList, time, previous);

    for (int query = 0; query < queries; query++)
    {
      int destination;
      std::cin >> destination;
      if (time[destination] == INF)
        std::cout << "Impossible" << nl;
      else
      {
        std::cout << time[destination] << nl;
        // std::cout << "Path: ";
        // printVector(restore_path(start, destination, previous));
      }
    }
  }
  return 0;
}
