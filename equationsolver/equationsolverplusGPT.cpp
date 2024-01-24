#include <iostream>
#include <cmath>

using namespace std;

typedef long double ld;

const int MAX_N = 110;
constexpr ld EPS = 1e-5L;

bool is_zero(ld x)
{
    return abs(x) < EPS;
}

struct AugmentedMatrix
{
    ld mat[MAX_N][MAX_N + 1];
};

struct ColumnVector
{
    ld vec[MAX_N];
    bool is_free[MAX_N];
};

// Helper function to print the matrix, useful for debugging
void debugPrintMatrix(int N, AugmentedMatrix Aug)
{
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j <= N; ++j)
        {
            cout << Aug.mat[i][j] << " ";
        }
        cout << endl;
    }
}

// Gauss Elimination with partial pivoting
pair<ColumnVector, bool> GaussElimination(int N, AugmentedMatrix &Aug)
{
    ColumnVector Ans;
    for (int i = 0; i < N; ++i)
    {
        Ans.is_free[i] = true; // Initially assume all variables are free
    }

    for (int i = 0; i < N; ++i)
    {
        // Find the pivot row
        int pivot = i;
        for (int row = i + 1; row < N; ++row)
        {
            if (abs(Aug.mat[row][i]) > abs(Aug.mat[pivot][i]))
            {
                pivot = row;
            }
        }

        // Swap the current row with the pivot row
        for (int k = i; k <= N; ++k)
        {
            swap(Aug.mat[i][k], Aug.mat[pivot][k]);
        }

        // If the pivot is zero, skip this row
        if (is_zero(Aug.mat[i][i]))
            continue;

        // Normalize the pivot row
        ld pivotValue = Aug.mat[i][i];
        for (int k = i; k <= N; ++k)
        {
            Aug.mat[i][k] /= pivotValue;
        }

        // Eliminate below
        for (int row = i + 1; row < N; ++row)
        {
            ld factor = Aug.mat[row][i];
            for (int k = i; k <= N; ++k)
            {
                Aug.mat[row][k] -= factor * Aug.mat[i][k];
            }
        }
    }

    // Back substitution
    for (int i = N - 1; i >= 0; --i)
    {
        if (is_zero(Aug.mat[i][i]))
        {
            continue; // If the pivot is zero, this variable is free
        }

        Ans.is_free[i] = false;
        Ans.vec[i] = Aug.mat[i][N];

        for (int j = i + 1; j < N; ++j)
        {
            if (!is_zero(Aug.mat[i][j]))
            {
                Ans.vec[i] -= Aug.mat[i][j] * Ans.vec[j];
            }
        }
    }

    // Check for inconsistency
    for (int i = 0; i < N; ++i)
    {
        bool non_zero_row = false; // Indicates if the row has non-zero coefficients
        for (int j = 0; j < N; ++j)
        {
            if (!is_zero(Aug.mat[i][j]))
            {
                non_zero_row = true;
                break;
            }
        }
        if (!non_zero_row && !is_zero(Aug.mat[i][N]))
        {
            return make_pair(Ans, false); // Inconsistent system
        }
    }

    return make_pair(Ans, true); // System has a solution
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);

    int n;
    while (cin >> n && n != 0)
    {
        AugmentedMatrix Aug;
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j <= n; ++j)
            {
                cin >> Aug.mat[i][j];
            }
        }

        auto [solution, solvable] = GaussElimination(n, Aug);

        if (!solvable)
        {
            cout << "inconsistent" << endl;
        }
        else
        {
            for (int i = 0; i < n; ++i)
            {
                if (solution.is_free[i])
                {
                    cout << "? ";
                }
                else
                {
                    cout << solution.vec[i] << " ";
                }
            }
            cout << endl;
        }
    }

    return 0;
}
