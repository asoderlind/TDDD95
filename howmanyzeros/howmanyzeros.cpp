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


ll countZerosUpTo(ll n)
{
    return 0;
}

ll countZeros(ll n)
{
    ll count = 0;
    while (n > 0)
    {
        if (n % 10 == 0)
            count++;
        n /= 10;
    }
    return count;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);
    ll n, m;

    while (cin >> n >> m)
    {
        if (n == -1 || m == -1)
            break;
        else {
            ll zeros = countZeros(m);
            ll lower = countZerosUpTo(m);
            ll upper = countZerosUpTo(n);
            cout << zeros + upper - lower << nl;
        }
    }

    // read input

    return 0;
}