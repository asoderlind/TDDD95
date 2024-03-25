/** TDDD95: Lab 3 - suffixsorting
 * Author: Axel Söderlind
 * Date:   2024-01-22
 * This problem is about suffix sorting. Given a string s of length n, you
 * are to compute the suffix array of s. The suffix array of s is an array of
 * integers, each in the range 0 to n−1, that describes the lexicographically
 * sorted list of all suffixes of s. That is, the suffix array is an array of i
 * ntegers p0, p1, . . . , pn−1 such that the suffixes s[p0], s[p1], . . . , s[pn−1]
 * are sorted in lexicographical order.
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef long double ld;

#define rep(i, a, b) for (int i = a; i < b; ++i)

bool DEBUG = true;

constexpr char nl = '\n';
constexpr ll INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 998244353;
constexpr ld EPS = 1e-9L;

// ------------------------------------------- //

void printPos(string str, vector<int> &pos)
{
    for (int i = 0; i < pos.size(); i++)
    {
        cout << pos[i] << ": " << str.substr(pos[i]) << nl;
    }
    cout << nl;
}

void printBucketHeads(vector<bool> &bucketHeads, vector<bool> &b2h)
{
    cout << "bucketHeads: ";
    for (int i = 0; i < bucketHeads.size(); i++)
    {
        cout << bucketHeads[i] << " ";
    }
    cout << nl;

    cout << "b2h: ";
    for (int i = 0; i < b2h.size(); i++)
    {
        cout << b2h[i] << " ";
    }
    cout << nl;
}

void printIntVector(vector<int> &v)
{
    for (int i = 0; i < v.size(); i++)
    {
        cout << v[i] << " ";
    }
    cout << nl;
}

struct SuffixArray
{
    string str;            // input
    int n;                 // length of the string
    vector<int> rank, pos; // output

    vector<int> count, next;       // internal
    vector<bool> bucketHeads, b2h; // internal

    bool smallerFirstChar(int a, int b) const
    {
        return str[a] < str[b];
    }

    SuffixArray(string input) : str(input), n(input.size()), rank(input.size()), pos(input.size()), count(input.size()), next(input.size()), bucketHeads(input.size()), b2h(input.size())
    {
        construct();
    }

    void construct()
    {
        // Initial sorting of positions based on the characters at those positions.
        for (int i = 0; i < n; ++i)
            pos[i] = i;

        if (DEBUG)
        {
            cout << "Initial pos:" << nl;
            printPos(str, pos);
        }

        // Sort positions based on the characters, using a lambda function for comparison
        sort(pos.begin(), pos.end(), [this](int a, int b)
             { return smallerFirstChar(a, b); });

        if (DEBUG)
        {
            cout << "After initial sorting:" << nl;
            printPos(str, pos);
        }

        // Initialize bucket heads and whether a character is in a bucket to be split (b2h)
        for (int i = 0; i < n; ++i)
        {
            // Mark the start of a new bucket if it's the
            // first character or different from the previous one
            bucketHeads[i] = i == 0 || str[pos[i]] != str[pos[i - 1]];
            // Split no buckets initially
            b2h[i] = false;
        }

        if (DEBUG)
        {
            printBucketHeads(bucketHeads, b2h);
        }

        // Doubling loop: in each iteration,
        // we compare suffixes based on their first 2^h characters
        for (int h = 1; h < n; h <<= 1) // h <<= 1 is equivalent to doubling h
        {
            int buckets = 0;

            // Init next array, which points to the start of the next bucket
            for (int i = 0, j; i < n; i = j)
            {
                j = i + 1;
                // Find the end of the current bucket
                while (j < n && !bucketHeads[j])
                    j++;
                next[i] = j; // next[i] points to the start of the next bucket
                buckets++;   // Increase the number of buckets
            }

            if (DEBUG)
            {
                cout << "number of buckets: " << buckets << nl;
                cout << "next bucket arr: ";
                printIntVector(next);
            }

            if (buckets == n)
                break; // If all suffixes are in their own bucket, stop

            // Assign ranks and prepare for the next phase
            for (int bucket = 0; bucket < n; bucket = next[bucket])
            {
                count[bucket] = 0; // Reset count for each bucket
                for (int j = bucket; j < next[bucket]; ++j)
                {
                    rank[pos[j]] = bucket; // Assign rank based on the bucket
                }
            }

            // Count the number of elements to be inserted into each bucket
            // and mark them for the next phase
            count[rank[n - h]]++;
            b2h[rank[n - h]] = true;
            for (int i = 0; i < n; i = next[i])
            {
                for (int j = i; j < next[i]; ++j)
                {
                    int s = pos[j] - h;
                    if (s >= 0)
                    {
                        int head = rank[s];
                        rank[s] = head + count[head]++;
                        b2h[rank[s]] = true; // Mark to indicate it's in a bucket to be split
                    }
                }
                // Clear the b2h flags for ranks that won't be split in the next phase
                for (int j = i; j < next[i]; ++j)
                {
                    int s = pos[j] - h;
                    if (s >= 0 && b2h[rank[s]])
                    {
                        for (int k = rank[s] + 1; !bucketHeads[k] && b2h[k]; k++)
                            b2h[k] = false;
                    }
                }
            }
            // Prepare for the next iteration
            for (int i = 0; i < n; ++i)
            {
                pos[rank[i]] = i; // Update positions based on ranks
                // Update bucketHeads to reflect the new bucket heads after splitting
                bucketHeads[i] = bucketHeads[i] | b2h[i];
            }
        }
        // Finalize the ranks for all positions
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