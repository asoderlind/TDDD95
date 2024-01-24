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
};

void debugPrintMatrix(int N, AugmentedMatrix Aug)
{
    for (int i = 0; i < N; ++i)
    {
        std::cout << "[ ";
        for (int j = 0; j <= N; ++j)
        {
            std::cout << Aug.mat[i][j] << " ";
        }
        std::cout << "]\n";
    }
}

/// @brief Performs Gauss Elimination on the augmented matrix (multiple solutions)
/// @param N number of equations
/// @param Aug the augmented matrix
/// @return the solution vector
pair<ColumnVector, ColumnVector> GaussElimination(int N, AugmentedMatrix Aug)
{
    for (int i = 0; i < N - 1; ++i)
    {
        // Find the row index with the largest absolute pivot
        // value and assign it to l
        int l = i;
        for (int j = i + 1; j < N; ++j)
        {
            if (Aug.mat[j][i] - Aug.mat[l][i] > EPS)
            {
                l = j;
            }
        }
        // swap row i with row l (row with largest pivot value)
        // this is to minimize floating point errors
        for (int k = i; k <= N; ++k)
            swap(Aug.mat[i][k], Aug.mat[l][k]);

        // Check if the row is all 0
        bool all_zero = true;
        for (int j = i; j <= N; ++j)
        {
            if (!is_zero(Aug.mat[i][j]))
            {
                all_zero = false;
                break;
            }
        }

        if (all_zero)
            continue;

        // Forward elimination
        for (int j = i + 1; j < N; ++j)
        {
            // Start from the back of each row and
            // subtract the row above multiplied by
            // the multiplier
            for (int k = N; k >= i; --k)
            {
                ld multiplier = (Aug.mat[j][i] / Aug.mat[i][i]);
                Aug.mat[j][k] -= Aug.mat[i][k] * multiplier;
            }
        }
    }

    // std::cout << "After forward elimination:\n";
    // debugPrintMatrix(N, Aug);

    // Backward substitution
    ColumnVector Ans = {0};
    ColumnVector FreeVars = {0};
    // the loop variable j represents the current
    // equation being considered
    for (int j = N - 1; j >= 0; --j)
    {
        if (is_zero(Aug.mat[j][j]))
        {
            FreeVars.vec[j] = 1;
            continue;
        }
        ld sum = 0.f;
        // the inner loop variable k represents the
        // current variable being considered
        for (int k = j + 1; k < N; ++k)
        {
            if (!is_zero(Aug.mat[j][k]) && abs(FreeVars.vec[k]) == 1)
            {
                FreeVars.vec[j] = 1;
                continue;
            }
            sum += Aug.mat[j][k] * Ans.vec[k];
        }
        ld variable_multiplier = Aug.mat[j][j];
        Ans.vec[j] = (Aug.mat[j][N] - sum) / variable_multiplier;
    }

    return {Ans, FreeVars};
}

/// @brief Checks the system of equations for consistency
/// @param N number of equations
/// @param Aug the augmented matrix
/// @return flag 0 if system has unique solution, 1 if multiple, 2 if inconsistent
int checkSystem(int N, AugmentedMatrix Aug)
{
    bool has_multiple = false;
    bool is_inconsistent = false;

    // Check row by row
    for (int i = 0; i < N && !is_inconsistent; ++i)
    {
        bool all_zero = true;

        // Go through the columns to check if all coefficients are 0
        for (int j = 0; j < N; j++)
        {
            if (Aug.mat[i][j] != 0)
            {
                all_zero = false;
                break;
            }
        }

        // If all the coefficients are 0, check if the RHS is 0
        if (all_zero)
        {
            if (Aug.mat[i][N] != 0)
                // 0 != 0 is inconsistent
                is_inconsistent = true;
            else
                // 0 == 0 results in inf solutions
                has_multiple = true;
            continue;
        }

        // Check for linear dependence
        for (int j = i + 1; j < N && !is_inconsistent; ++j)
        {
            ld factor = -1;
            bool parallel = true;
            bool factor_is_set = false;

            for (int k = 0; k < N && parallel; k++)
            {
                // if variable is 0 for both equations, skip
                if (abs(Aug.mat[i][k]) == 0 && abs(Aug.mat[j][k]) == 0)
                    continue;

                // if one is 0 and the other is not, not parallel
                if (abs(Aug.mat[i][k]) == 0 || abs(Aug.mat[j][k]) == 0)
                {
                    parallel = false;
                }
                // if factor not set, set it
                else
                {
                    if (!factor_is_set)
                    {
                        // Set factor to the ratio of the coefficients
                        factor = Aug.mat[i][k] / Aug.mat[j][k];
                        factor_is_set = true;
                    }
                    else
                    {
                        // if the ratio is not the same, not parallel
                        if (abs(factor - Aug.mat[i][k] / Aug.mat[j][k]) > 1e-9)
                        {
                            parallel = false;
                        }
                    }
                }
            }

            if (!parallel)
                continue;
            // If we suspect linear dependence, check if the RHS is the same
            if (abs(factor * Aug.mat[j][N] - Aug.mat[i][N]) > 1e-9)
            {
                // If the RHS is not the same, inconsistent
                is_inconsistent = true;
            }
            else
            {
                // If the RHS is the same, multiple solutions
                has_multiple = true;
            }
        }
    }

    if (is_inconsistent)
        return 2;
    if (has_multiple)
        return 1;
    return 0;
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
            for (int j = 0; j < n; ++j)
            {
                cin >> Aug.mat[i][j];
            }
        }
        for (int i = 0; i < n; ++i)
        {
            cin >> Aug.mat[i][n];
        }
        int flag = checkSystem(n, Aug);
        if (flag == 2)
        {
            std::cout << "inconsistent" << endl;
        }
        else
        {
            auto [x, free] = GaussElimination(n, Aug);
            for (int i = 0; i < n; ++i)
            {
                if (free.vec[i])
                {
                    std::cout << "? ";
                }
                else
                {
                    std::cout << x.vec[i] << " ";
                }
            }
            std::cout << endl;
        }
    }

    return 0;
}