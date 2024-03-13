/** TDDD95: Lab X - <name>
 * Author: Axel Söderlind
 * Date:   2024-01-22
 * This problem is about ...
 */
#include <iostream>
#include <vector>
#include <algorithm>

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

const bool VERBOSE = true;

// boolean array of visited cells
bool visited[8][8];
// distance array
int dist[8][8];

int deltaRow[] = {-2, -1, 1, 2, 2, 1, -1, -2}; // change in row
int deltaCol[] = {1, 2, 2, 1, -1, -2, -2, -1}; // change in column

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int numCases;
    cin >> numCases;

    for (int i = 0; i < numCases; ++i)
    {
        // read input
        string start;
        cin >> start;
        int startRow = start[1] - '1';
        int startCol = start[0] - 'a';

        // initialize visited and dist arrays
        for (int i = 0; i < 8; ++i)
        {
            for (int j = 0; j < 8; ++j)
            {
                visited[i][j] = false;
                dist[i][j] = 0;
            }
        }

        // queue of cells to visit
        vector<pair<int, int>> q;

        // add starting cell to queue
        q.push_back(make_pair(startRow, startCol));

        // BFS
        while (!q.empty())
        {
            pair<int, int> cell = q.front();
            q.erase(q.begin());
            int row = cell.first;
            int col = cell.second;
            for (int i = 0; i < 8; ++i)
            {
                int newRow = row + deltaRow[i];
                int newCol = col + deltaCol[i];
                if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8 && !visited[newRow][newCol])
                {
                    visited[newRow][newCol] = true;
                    dist[newRow][newCol] = dist[row][col] + 1;
                    q.push_back(make_pair(newRow, newCol));
                }
            }
        }

        // find max distance
        int maxDist = 0;
        for (int i = 0; i < 8; ++i)
        {
            for (int j = 0; j < 8; ++j)
            {
                maxDist = max(maxDist, dist[i][j]);
            }
        }

        cout << maxDist;
        for (int i = 8; i >= 0; --i)
        {
            for (int j = 0; j < 8; ++j)
            {
                if (dist[i][j] == maxDist)
                {
                    cout << " " << (char)('a' + j) << (i + 1);
                }
            }
        }
        cout << nl;
    }

    return 0;
}