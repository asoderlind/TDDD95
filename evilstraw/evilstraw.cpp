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

int getNumSwaps(string s)
{
    int numSwaps = 0;
    int n = s.size();
    for (int i = 0; i < n / 2; ++i)
    {
        if (s[i] != s[n - i - 1])
        {
            numSwaps++;
        }
    }
    return numSwaps;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    // read input
    int numCases;
    cin >> numCases;

    for (int i = 0; i < numCases; ++i)
    {
        // read input
        string s;
        cin >> s;
        int numSwaps = getNumSwaps(s);
        cout << s << ": " << numSwaps << nl;
    }

    return 0;
}