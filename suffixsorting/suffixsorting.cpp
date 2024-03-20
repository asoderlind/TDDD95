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

struct SuffixArray
{
    string str;            // input
    int n;                 // length of the string
    vector<int> rank, pos; // output

    vector<int> cnt, next; // internal
    vector<bool> bh, b2h;  // internal

    bool smaller_first_char(int a, int b) const
    {
        return str[a] < str[b];
    }

    SuffixArray(string input) : str(input), n(input.size()), rank(input.size()), pos(input.size()), cnt(input.size()), next(input.size()), bh(input.size()), b2h(input.size())
    {
        construct();
    }

    void construct()
    {
        for (int i = 0; i < n; ++i)
        {
            pos[i] = i;
        }

        sort(pos.begin(), pos.end(), [this](int a, int b)
             { return smaller_first_char(a, b); });

        for (int i = 0; i < n; ++i)
        {
            bh[i] = i == 0 || str[pos[i]] != str[pos[i - 1]];
            b2h[i] = false;
        }

        for (int h = 1; h < n; h <<= 1)
        {
            int buckets = 0;
            for (int i = 0, j; i < n; i = j)
            {
                j = i + 1;
                while (j < n && !bh[j])
                    j++;
                next[i] = j;
                buckets++;
            }
            if (buckets == n)
                break;

            for (int i = 0; i < n; i = next[i])
            {
                cnt[i] = 0;
                for (int j = i; j < next[i]; ++j)
                {
                    rank[pos[j]] = i;
                }
            }

            cnt[rank[n - h]]++;
            b2h[rank[n - h]] = true;
            for (int i = 0; i < n; i = next[i])
            {
                for (int j = i; j < next[i]; ++j)
                {
                    int s = pos[j] - h;
                    if (s >= 0)
                    {
                        int head = rank[s];
                        rank[s] = head + cnt[head]++;
                        b2h[rank[s]] = true;
                    }
                }
                for (int j = i; j < next[i]; ++j)
                {
                    int s = pos[j] - h;
                    if (s >= 0 && b2h[rank[s]])
                    {
                        for (int k = rank[s] + 1; !bh[k] && b2h[k]; k++)
                            b2h[k] = false;
                    }
                }
            }
            for (int i = 0; i < n; ++i)
            {
                pos[rank[i]] = i;
                bh[i] = bh[i] | b2h[i];
            }
        }
        for (int i = 0; i < n; ++i)
        {
            rank[pos[i]] = i;
        }
    }

    int getSuffix(int i)
    {
        return pos[i];
    }
};

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    while (true)
    {
        string s;
        getline(cin, s);
        if (DEBUG)
        {
            cout << "s: " << s << nl;
        }
        if (s.empty())
        {
            break;
        }

        SuffixArray suffixObject(s);

        int n;
        cin >> n;
        for (int i = 0; i < n; i++)
        {
            int x;
            cin >> x;
            cout << suffixObject.getSuffix(x) << " ";
        }
        cout << nl;
        getline(cin, s);
    }

    return 0;
}