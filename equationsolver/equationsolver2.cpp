/** TDDD95: Lab 1 - equationsolver
 * Author: Axel Söderlind
 * Date:   2024-03-06
 * This problem is about solving a system of linear equations.
 * We use Gaussian Elimination to solve this problem. We first
 * perform forward elimination to get the matrix in row echelon
 * form. We then perform backward substitution to get the
 * solution vector. We also check the system of equations for
 * consistency and linear dependence.
 *
 * Complexity: O(n^3) where n is the number of equations.
 * Space: O(n^2) where n is the number of equations.
 */
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

typedef long double ld;

constexpr ld EPS = 1e-5L;

/// @brief Checks if a number is zero
/// @param x
/// @return true if x is zero, false otherwise
bool is_zero(ld x)
{
    return abs(x) < EPS;
}

/// @brief Performs Gauss Elimination on the augmented matrix (multiple solutions)
/// @param N number of equations
/// @param Aug the augmented matrix
/// @param verbose whether to print the augmented matrix
/// @return the solution vector
pair<vector<ld>, vector<bool>> GaussElimination(int N, vector<vector<ld>> Aug, bool verbose = false)
{
    int num_rows = Aug.size();
    int num_cols = (int)Aug[0].size() - 1;

    // Keep track of the pivot columns
    vector<int> pivot;
    // outer loop variable j represents the current
    // column being considered
    // r keeps track of row to start inner loop at
    for (int j = 0, r = 0; j < num_cols; j++)
    {
        // Keep track of the max absolute value in the
        // current column and the row it is in
        pair<ld, int> best(0, -1);

        // inner loop variable i represents the current
        // row being considered, starting at r
        for (int i = r; i < num_rows; i++)
        {
            // if the current element is greater than the
            // current max, update the max
            best = max(best, pair(abs(Aug[i][j]), i));
        }
        // if the max is greater than EPS, it means
        // there is a nonzero element in the column
        // and we can pivot
        if (best.first > EPS)
        {
            // swap the current row with the row with the
            // max element
            swap(Aug[r], Aug[best.second]);

            // Go through the rows below the current row
            // and eliminate the current column
            for (int i = r + 1; i < num_rows; i++)
            {
                ld multiplier = Aug[i][j] / Aug[r][j];
                for (int k = j; k <= num_cols; k++)
                {
                    Aug[i][k] -= Aug[r][k] * multiplier;
                }
            }
            pivot.push_back(j);
            r++;
        }
    }

    // After forward elimination, refine the matrix to its row-echelon form
    int num_pivots = pivot.size();
    for (int i = 0; i < num_pivots; i++)
    {
        for (int k = 0; k < i; k++)
        {
            ld f = Aug[k][pivot[i]] / Aug[i][pivot[i]];
            for (int j = pivot[i]; j <= num_cols; j++)
            {
                Aug[k][j] -= Aug[i][j] * f;
            }
        }
    }

    // print the augmented matrix
    if (verbose)
    {
        for (int i = 0; i < num_rows; i++)
        {
            for (int j = 0; j <= num_cols; j++)
            {
                if (j == num_cols)
                    cerr << "| ";
                cerr << Aug[i][j] << " ";
            }
            cerr << "\n";
        }
    }

    // Check for inconsistent system
    for (int i = num_pivots; i < num_rows; i++)
    {
        if (!is_zero(Aug[i][num_cols]))
        {
            return {{}, {}}; // Return empty vectors if the system is inconsistent
        }
    }

    // Backward substitution to find the solution vector
    vector<ld> Ans(num_cols);
    vector<bool> FreeVars(num_cols, true); // Init all variables as free
    // the loop variable j represents the current
    // equation being considered
    for (int i = num_pivots - 1; i >= 0; i--)
    {
        bool single = true;               // Flag to check if the current variable is a free variable
        Ans[pivot[i]] = Aug[i][num_cols]; // Set the initial value of the solution for the current variable

        // Calculate the actual value of the variable by considering its dependencies
        for (int j = pivot[i] + 1; j < num_cols; j++)
        {
            Ans[pivot[i]] -= Ans[j] * Aug[i][j];
            single &= is_zero(Aug[i][j]); // If the current variable depends on another, it is not free
        }
        Ans[pivot[i]] /= Aug[i][pivot[i]]; // Normalize the solution for the current variable

        // If the variable is not dependent on others, mark it as not free
        if (single)
        {
            FreeVars[pivot[i]] = false;
        }
    }
    return pair(Ans, FreeVars);
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);

    int n;
    while (cin >> n && n != 0)
    {
        vector Aug(n, vector<ld>(n + 1));
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                cin >> Aug[i][j];
            }
        }
        for (int i = 0; i < n; ++i)
        {
            cin >> Aug[i][n];
        }
        auto [x, free] = GaussElimination(n, Aug);
        bool hasMultiple = false;
        if (x.empty())
        {
            std::cout << "inconsistent" << endl;
        }
        else
        {
            for (int i = 0; i < n; ++i)
            {
                if (free[i])
                {
                    std::cout << "multiple " << endl;
                    hasMultiple = true;
                    break;
                }
            }
            if (!hasMultiple)
            {
                for (int i = 0; i < n; ++i)
                    std::cout << x[i] << " ";
                std::cout << endl;
            }
        }
    }

    return 0;
}