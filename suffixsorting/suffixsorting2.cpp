/** TDDD95: Lab 3 - suffixsorting
 * Author: Axel Söderlind
 * Date:   2024-01-22
 * This problem is about suffix sorting. Given a string s of length n, you
 * are to compute the suffix array of s. The suffix array of s is an array of
 * integers, each in the range 0 to n−1, that describes the lexicographically
 * sorted list of all suffixes of s. That is, the suffix array is an array of i
 * ntegers p0, p1, . . . , pn−1 such that the suffixes s[p0], s[p1], . . . , s[pn−1]
 * are sorted in lexicographical order.
 *
 * Time complexity O(n * logn * logn)
 * Space complexity O(n)
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

struct suffix
{
    int index;   // To store original index
    int rank[2]; // To store ranks and next rank pair
};

// Compares two pairs, returns 1 if first pair is smaller
int cmpSuffixPairs(struct suffix a, struct suffix b)
{
    return (a.rank[0] == b.rank[0]) ? (a.rank[1] < b.rank[1] ? 1 : 0) : (a.rank[0] < b.rank[0] ? 1 : 0);
}

struct SuffixArray
{
    string str; // input
    int n;      // length of the string
    suffix *suffixes;
    vector<int> suffixArr;

    SuffixArray(string input) : str(input), n(input.size()), suffixes(new suffix[n]), suffixArr(n)
    {
        construct();
    }

    void construct()
    {
        for (int i = 0; i < n; i++)
        {
            suffixes[i].index = i;
            suffixes[i].rank[0] = str[i] - 'a';                            // store ASCII value of char as rank
            suffixes[i].rank[1] = ((i + 1) < n) ? (str[i + 1] - 'a') : -1; // value of adjascent char
        }

        sort(suffixes, suffixes + n, cmpSuffixPairs); // sort according to rank and next rank

        if (DEBUG)
            printSuffixes();

        int suffixMap[n]; // map original suffix index to suffixes[] index
        for (int h = 4; h < 2 * n; h = h * 2)
        {
            // Assigning rank and index values to first suffix
            int rank = 0;
            int prev_rank = suffixes[0].rank[0];
            suffixes[0].rank[0] = rank;
            suffixMap[suffixes[0].index] = 0;

            // Assigning rank to suffixes
            for (int i = 1; i < n; i++)
            {
                // If first rank and next ranks are same as that of previous
                // suffix in array, assign the same new rank to this suffix
                if (suffixes[i].rank[0] == prev_rank &&
                    suffixes[i].rank[1] == suffixes[i - 1].rank[1])
                {
                    prev_rank = suffixes[i].rank[0];
                    suffixes[i].rank[0] = rank;
                }
                else // Otherwise increment rank and assign
                {
                    prev_rank = suffixes[i].rank[0];
                    suffixes[i].rank[0] = ++rank;
                }
                suffixMap[suffixes[i].index] = i;
            }

            // Assign next rank to every suffix
            for (int i = 0; i < n; i++)
            {
                int nextindex = suffixes[i].index + h / 2;
                suffixes[i].rank[1] = (nextindex < n) ? suffixes[suffixMap[nextindex]].rank[0] : -1;
            }

            // Sort the suffixes according to first h characters
            sort(suffixes, suffixes + n, cmpSuffixPairs);

            if (DEBUG)
                printSuffixes();
        }

        // Store indexes of all sorted suffixes in the suffix array
        for (int i = 0; i < n; i++)
            suffixArr[i] = suffixes[i].index;
    }

    int getSuffix(int i)
    {
        return suffixArr[i];
    }

    void printSuffixes()
    {
        cout << "index\trank1\trank2" << nl;
        for (int i = 0; i < n; i++)
        {
            cout << suffixes[i].index << "\t" << suffixes[i].rank[0] << "\t" << suffixes[i].rank[1] << nl;
        }
        cout << nl;
    }

    void printSuffixArray()
    {
        cout << "suffixArr: " << nl;
        for (int i = 0; i < suffixArr.size(); i++)
        {
            cout << suffixArr[i] << " ";
        }
        cout << nl;
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

        if (DEBUG)
        {
            suffixObject.printSuffixArray();
            suffixObject.printSuffixes();
        }

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