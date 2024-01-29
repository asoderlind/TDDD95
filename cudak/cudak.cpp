// Including necessary header files
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Type definitions for convenience
typedef long long ll;
typedef long double ld;

// Constants for newline character, infinity values, modulus value, and epsilon value
constexpr char nl = '\n';
constexpr ll INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 998244353;
constexpr ld EPS = 1e-9L;

ll a, b, s;
const int siz = 18, S = 136;
ll dp[siz][S]; // Dynamic programming table

// Initialize the dynamic programming table
void init()
{
    // Set all values to 0 initially
    for (int i = 0; i < siz; i++)
        for (int j = 0; j < S; j++)
            dp[i][j] = 0;

    // Base cases for the DP table
    dp[0][0] = 1;
    for (int i = 0; i < 10; i++)
        dp[1][i] = 1;

    // Fill the DP table based on the number of digits and their sums
    for (int i = 2; i < siz; i++)
        for (int j = 0; j < S; j++)
            for (int k = 0; k < 10 && j - k >= 0; k++)
                dp[i][j] += dp[i - 1][j - k];
}

// Function to calculate the sum of digits of a number
int sumOfDigits(int number)
{
    int sum = 0;
    while (number > 0)
    {
        sum += number % 10;
        number /= 10;
    }
    return sum;
}

// Function to count the number of digits in a number
int numDigits(int number)
{
    int count = 0;
    while (number > 0)
    {
        ++count;
        number /= 10;
    }
    return count;
}

/// @brief Function to calculate the number of integers within the range [A, B] with a sum of S
/// @param A Starting value of range
/// @param B Ending value of range
/// @param S Target sum of digits
/// @param verbose Flag for printing detailed output
/// @return A pair of integers: first is the count of numbers with sum S, second is the smallest such number
pair<int, int> cudak(int A, int B, int S, bool verbose = false)
{
    int count = 0;
    ll lowest = INF;
    if (verbose)
        cout << "[" << A << ", " << B << "], S = " << S << nl;
    // Loop through the range to find numbers with sum of digits equal to S
    for (int i = A; i <= B; ++i)
    {
        if (sumOfDigits(i) == S)
        {
            if (verbose)
                cout << i << " is a solution\n";
            ++count;
            lowest = min(lowest, (ll)i);
        }
    }
    if (verbose)
        cout << "count = " << count << ", lowest = " << lowest << nl;
    return {count, lowest};
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);
    init(); // Initialize DP table

    // Debugging: print parts of the DP table
    for (int i = 0; i < siz; i++)
    {
        for (int j = 0; j < 50; j++)
            cout << dp[i][j] << " ";
        cout << "..." << nl;
    }
    cout << dp[2][10] << nl;

    int A, B, S;

    // Read input values for the range and target sum
    cin >> A >> B >> S;

    // Calculate and output the results
    auto [n, x] = cudak(A, B, S);
    cout << n << nl << x << nl;

    return 0;
}
