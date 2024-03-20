/** TDDD95: Lab 3.1 - stringmatching
 * Author: Axel Söderlind
 * Date:   2024-03-20
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

/// @brief a function that computes the pi array for the KMP algorithm
/// @param pat
/// @param M
/// @param lps
void computePi(string p, int m, vector<int> &pi)
{
    int len = 0; // length of the previous longest prefix suffix
    pi[0] = 0;

    // calculate pi[i] for i = 1 to m-1
    int i = 1;
    while (i < m)
    {
        if (p[i] == p[len])
        {
            len++;
            pi[i] = len;
            i++;
        }
        else // (pat[i] != pat[len])
        {
            // This is tricky. Consider the example.
            // AAACAAAA and i = 7. The idea is similar
            // to search step.
            if (len != 0)
            {
                len = pi[len - 1];

                // Also, note that we do not increment
                // i here
            }
            else // if (len == 0)
            {
                pi[i] = 0;
                i++;
            }
        }
    }
}

/// @brief a function that returns the indexes of all occurences of p in s
/// @param s The string to search in
/// @param p The pattern to search for
/// @return A vector of indexes where p is found in s
vector<int> findMatches(const string &s, const string &p)
{
    vector<int> res;
    int n = s.size(); // length of string
    int m = p.size(); // length of pattern
    vector<int> pi(m);

    computePi(p, m, pi);
    // print pi

    int i = 0; // index for txt[]
    int j = 0; // index for pat[]
    while ((n - i) >= (m - j))
    {
        if (p[j] == s[i])
        {
            j++;
            i++;
        }

        if (j == m)
        {
            if (DEBUG)
                printf("Found pattern at index %d \n", i - j);
            res.push_back(i - j);
            j = pi[j - 1];
        }

        // mismatch after j matches
        else if (i < n && p[j] != s[i])
        {
            // Do not match lps[0..lps[j-1]] characters,
            // they will match anyway
            if (j != 0)
                j = pi[j - 1];
            else
                i = i + 1;
        }
    }
    return res;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    if (DEBUG)
    {
        cout << "DEBUG is on" << nl;
    }

    // read input strings on two lines
    string s, p;
    while (true)
    {
        getline(cin, p);
        getline(cin, s);

        if (s.empty() || p.empty())
        {
            break;
        }

        if (DEBUG)
        {
            cout << "pattern: " << p << nl;
            cout << "string: " << s << nl;
        }

        vector<int> res = findMatches(s, p);

        // print output
        for (int i : res)
        {
            cout << i << " ";
        }
        cout << nl;
    }

    return 0;
}