/** TDDD95: Lab 3.1 - String Matching
 * Author: Axel Söderlind
 * Date:   2024-03-20
 * This program demonstrates the Knuth-Morris-Pratt (KMP) algorithm for string matching.
 * It reads pairs of strings from standard input, where the first string in each pair is
 * the pattern and the second is the text to search within. For each pair, the program outputs
 * the starting indexes of all occurrences of the pattern within the text.
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

/// @brief Computes the longest proper prefix that is also a suffix (LPS) array for the KMP algorithm
/// @param p The pattern string
/// @param m The length of the pattern
/// @param pi Reference to an integer vector where the LPS array will be stored
void computePi(string p, int m, vector<int> &pi)
{
    int len = 0; // Length of the previous longest prefix suffix
    pi[0] = 0;   // LPS[0] is always 0

    // Calculate pi[i] for i = 1 to m-1
    int i = 1;
    while (i < m)
    {
        if (p[i] == p[len])
        {
            len++;
            pi[i] = len;
            i++;
        }
        else
        {
            if (len != 0)
            {
                len = pi[len - 1];
            }
            else
            {
                pi[i] = 0;
                i++;
            }
        }
    }
}

/// @brief Finds all occurrences of the pattern in the given text and returns their starting indexes
/// @param s The text string to search in
/// @param p The pattern string to search for
/// @return A vector of integers containing the starting indexes of all occurrences of the pattern in the text
vector<int> findMatches(const string &s, const string &p)
{
    vector<int> res;
    int n = s.size(); // Length of the text
    int m = p.size(); // Length of the pattern
    vector<int> pi(m);

    computePi(p, m, pi);

    int i = 0; // Index for text
    int j = 0; // Index for pattern
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
        else if (i < n && p[j] != s[i])
        {
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

    // Continuously read pattern and text strings from standard input until an empty line is encountered
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

        // Print the starting indexes of all occurrences of the pattern in the text
        for (int i : res)
        {
            cout << i << " ";
        }
        cout << nl;
    }

    return 0;
}
