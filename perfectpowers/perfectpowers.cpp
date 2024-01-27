/** TDDD95: Lab X - <name>
 * Author: Axel Söderlind
 * Date:   2024-01-22
 * This problem is about ...
 */
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef long double ld;

constexpr char nl = '\n';
constexpr ll INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 998244353;
constexpr ld EPS = 1e-9L;

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    ll x;
    while (cin >> x && x != 0)
    {
        if (x == 0)
            break;

        int p = 35;
        while (p)
        {
            if (pow(round(pow(abs(x), 1.0 / p)), p) == abs(x))
            {
                cout << p << nl;
                break;
            }
            p -= 1 + (x < 0);
        }
    }
    return 0;
}