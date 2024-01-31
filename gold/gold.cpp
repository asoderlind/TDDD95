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

constexpr char nl = '\n';
constexpr ll INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 998244353;
constexpr ld EPS = 1e-9L;

char graph[50][50];
int visited[50][50] = {0};
int W, H;

struct Coordinate
{
    int x;
    int y;
};

Coordinate P;

bool isValid(int x, int y)
{
    return x >= 0 && x < H && y >= 0 && y < W && graph[x][y] != '#' && visited[x][y] < 1;
}

bool isSafe(Coordinate c)
{
    int dx[] = {1, -1, 0, 0};
    int dy[] = {0, 0, 1, -1};
    for (int i = 0; i < 4; i++)
    {
        int nx = c.x + dx[i];
        int ny = c.y + dy[i];
        if (isValid(nx, ny) && graph[nx][ny] == 'T')
        {
            return false;
        }
    }
    return true;
}

int searchForGold(Coordinate c)
{
    if (!isValid(c.x, c.y))
        return 0;

    if (!isSafe(c))
    {
        visited[c.x][c.y] = 2;
        return (graph[c.x][c.y] == 'G') ? 1 : 0;
    }

    visited[c.x][c.y] = 1;
    int gold = (graph[c.x][c.y] == 'G') ? 1 : 0;

    int dx[] = {1, -1, 0, 0};
    int dy[] = {0, 0, 1, -1};
    for (int i = 0; i < 4; i++)
    {
        Coordinate next = {c.x + dx[i], c.y + dy[i]};
        gold += searchForGold(next);
    }

    return gold;
}

/// @brief Initialize the graph and player coordinate
void init()
{
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            cin >> graph[i][j];
            if (graph[i][j] == 'P')
            {
                P.x = i;
                P.y = j;
            }
        }
    }
}

void printGraphs()
{
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            cout << visited[i][j];
        }
        cout << nl;
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    // first two integers represent width and height of map
    cin >> W >> H;

    init();
    // cout << " W: " << W << " H: " << H << nl;
    cout << searchForGold(P) << nl;
    return 0;
}