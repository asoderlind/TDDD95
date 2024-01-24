#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

typedef long double ld;

constexpr char nl = '\n';
constexpr ld EPS = 1e-5L;

bool is_zero(ld x)
{
    return abs(x) < EPS;
}

pair<vector<ld>, vector<bool>> solve(vector<vector<ld>> a, bool verbose = false)
{
    int n = a.size();
    int m = (int)a[0].size() - 1;

    vector<int> pivot;
    for (int j = 0, r = 0; j < m; j++)
    {
        pair<ld, int> best(0, -1);
        for (int i = r; i < n; i++)
        {
            best = max(best, pair(abs(a[i][j]), i));
        }
        if (best.first > EPS)
        {
            swap(a[r], a[best.second]);
            for (int i = r + 1; i < n; i++)
            {
                ld f = a[i][j] / a[r][j];
                for (int k = j; k <= m; k++)
                {
                    a[i][k] -= a[r][k] * f;
                }
            }
            pivot.push_back(j);
            r++;
        }
    }

    int r = pivot.size();
    for (int i = 0; i < r; i++)
    {
        for (int k = 0; k < i; k++)
        {
            ld f = a[k][pivot[i]] / a[i][pivot[i]];
            for (int j = pivot[i]; j <= m; j++)
            {
                a[k][j] -= a[i][j] * f;
            }
        }
    }

    if (verbose)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j <= m; j++)
            {
                if (j == m)
                    cerr << "| ";
                cerr << a[i][j] << " ";
            }
            cerr << nl;
        }
    }

    for (int i = r; i < n; i++)
    {
        if (!is_zero(a[i][m]))
        {
            return {{}, {}};
        }
    }

    vector<ld> res(m);
    vector<bool> free(m, true);
    for (int i = r - 1; i >= 0; i--)
    {
        bool single = true;
        res[pivot[i]] = a[i][m];
        for (int j = pivot[i] + 1; j < m; j++)
        {
            res[pivot[i]] -= res[j] * a[i][j];
            single &= is_zero(a[i][j]);
        }
        res[pivot[i]] /= a[i][pivot[i]];
        if (single)
        {
            free[pivot[i]] = false;
        }
    }
    return pair(res, free);
}

// double-check correctness
// read limits carefully
// characterize valid solutions
int main()
{
    cin.tie(0)->sync_with_stdio(0);

    for (int n; cin >> n && n;)
    {
        vector a(n, vector<ld>(n + 1));
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cin >> a[i][j];
            }
        }
        for (int i = 0; i < n; i++)
        {
            cin >> a[i][n];
        }
        auto [x, free] = solve(a);
        if (x.empty())
        {
            cout << "inconsistent" << nl;
        }
        else
        {
            for (int i = 0; i < n; i++)
            {
                if (free[i])
                {
                    cout << "? ";
                }
                else
                {
                    cout << x[i] << " ";
                }
            }
            cout << nl;
        }
    }

    return 0;
}
