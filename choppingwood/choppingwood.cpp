#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

typedef long long ll;
typedef long double ld;

constexpr char nl = '\n';
constexpr ll INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 998244353;
constexpr ld EPS = 1e-9L;

vector<int> get_degrees(vector<int> list)
{
    int max = *max_element(list.begin(), list.end());
    vector<int> degrees(max, 0);
    for (int i = 0; i < list.size(); i++)
    {
        degrees[list[i] - 1]++;
    }
    return degrees;
}

vector<int> choppingwood(int n, vector<int> &v, bool verbose = false)
{
    // First check
    if (v[n - 1] != n + 1)
    {
        return vector<int>();
    }
    // Init lists
    vector<int> d = get_degrees(v);
    vector<int> outList(v.size(), 0);
    priority_queue<int, vector<int>, greater<int>> zero_indices;
    // Print
    if (verbose)
    {
        cout << "degrees: [";
        for (int i = 0; i < d.size(); i++)
        {
            cout << d[i] << ",";
        }
        cout << "]" << nl;
    }
    // init queue
    for (int i = 0; i < d.size(); i++)
    {
        if (d[i] == 0)
        {
            zero_indices.push(i); // indices of the zeroes
        }
    }
    if (verbose)
    {
        // copy queue
        priority_queue<int, vector<int>, greater<int>> zero_indices_copy = zero_indices;
        cout << "zero_indices: [";
        while (!zero_indices_copy.empty())
        {
            cout << zero_indices_copy.top() << ",";
            zero_indices_copy.pop();
        }
        cout << "]" << nl;
    }
    // stop if no zero_indices
    if (zero_indices.empty())
    {
        return vector<int>();
    }
    // loop over zero_indices
    for (int i = 0; i < v.size(); i++)
    {
        int current_leaf = v[i]; // 5
        int first_zero_index = zero_indices.top();
        zero_indices.pop();
        if (verbose)
        {
            cout << "first_zero_index: " << first_zero_index << nl;
            cout << "v[first_zero_index]: " << v[first_zero_index] << nl;
        }
        outList[i] = first_zero_index + 1;
        --d[current_leaf - 1]; // decrement the degree of the parent
        if (d[current_leaf - 1] == 0)
        {
            zero_indices.push(current_leaf - 1);
        }
    }
    return outList;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    // read input
    int n;
    cin >> n;
    vector<int> v(n, 0);
    for (int i = 0; i < n; i++)
        cin >> v[i];

    vector<int> outList = choppingwood(n, v, false);
    if (outList.size() == 0)
    {
        cout << "Error" << nl;
        return 0;
    }
    else
    {
        for (int i = 0; i < outList.size(); i++)
        {
            cout << outList[i] << nl;
        }
    }
    return 0;
}