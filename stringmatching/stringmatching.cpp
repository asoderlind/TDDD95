/** TDDD95: Lab 3.1 - stringmatching
 * Author: Axel Söderlind
 * Date:   2024-03-20
 * This program demonstrates the Knuth-Morris-Pratt (KMP) algorithm for string matching.
 * It reads pairs of strings from standard input, where the first string in each pair is
 * the pattern and the second is the text to search within. For each pair, the program outputs
 * the starting indexes of all occurrences of the pattern within the text. The purpose of computing
 * the LPS array is to facilitate the KMP algorithm's ability to skip over portions of the text
 * where a match is not possible
 *
 * Time complexity: O(n + m) where n is the length of the text and m is the length of the pattern.
 * Space complexity: O(m) where m is the length of the pattern.
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
/// @param lps Reference to an integer vector where the LPS array will be stored
void computeLps(string pattern, int patternLen, vector<int> &lps)
{
    int len = 0; // Length of the previous longest prefix suffix
    lps[0] = 0;  // lps[0] is always 0

    // Calculate lps[i] for i = 1 to m-1
    int i = 1;
    while (i < patternLen)
    {
        if (pattern[i] == pattern[len])
        {
            // If the characters match, increment the length and store it in the LPS array
            len++;
            lps[i] = len;
            i++;
        }
        else
        {
            // If the characters do not match
            if (len != 0)
            {
                // Move len to the index of the previous longest prefix suffix
                len = lps[len - 1];
            }
            else
            {
                // If len is 0, set lps[i] to 0 and increment i
                lps[i] = 0;
                i++;
            }
        }
    }
}

/// @brief Finds all occurrences of the pattern in the given text and returns their starting indexes
/// @param s The text string to search in
/// @param p The pattern string to search for
/// @return A vector of integers containing the starting indexes of all occurrences of the pattern in the text
vector<int> findMatches(const string &str, const string &pattern)
{
    vector<int> occurrences;
    int stringLen = str.size();      // Length of the text
    int patternLen = pattern.size(); // Length of the pattern
    vector<int> lps(patternLen);     // LPS array for the pattern

    computeLps(pattern, patternLen, lps);

    if (DEBUG)
    {
        cout << "LPS array: ";
        for (int i : lps)
        {
            cout << i << " ";
        }
        cout << nl;
    }

    int i = 0; // Index for text
    int j = 0; // Index for pattern
    while ((stringLen - i) >= (patternLen - j))
    {
        if (pattern[j] == str[i])
        {
            j++;
            i++;
        }

        if (j == patternLen)
        {
            occurrences.push_back(i - j);
            j = lps[j - 1];
        }
        else if (i < stringLen && pattern[j] != str[i])
        {
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }
    return occurrences;
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
