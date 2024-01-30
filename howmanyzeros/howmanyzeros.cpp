/** TDDD95: Lab X - <name>
 * Author: Axel Söderlind
 * Date:   2024-01-22
 * This problem is about ...
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef long double ld;

constexpr char nl = '\n';
constexpr ll INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 998244353;
constexpr ld EPS = 1e-9L;


long countZerosUpTo(long n, bool verbose = false) {
        long zeros = 0;
        long digit, sliceLeft, sliceRight;
        
        if (verbose) {
            printf("n: %ld\n", n);
        }

        for (int i = 1; ; i *= 10) {

            // Slice number and get middle digit
            digit = n / i;
            sliceRight = n % i;
            sliceLeft = digit / 10;
            digit = digit % 10;

            if (verbose) {
                printf("digit: %ld, sliceLeft: %ld, sliceRight: %ld\n", digit, sliceLeft, sliceRight);
            }

            // Whole number processed
            if (sliceLeft == 0) {
                if (verbose) {
                    printf("reached end of number\n");
                }
                return zeros;
            }

            // Special case for digit zero
            if (verbose) {
                printf("zeros before: %ld\n", zeros);
            }
            if (digit == 0) {
                if (verbose) {
                    printf("zeros += %ld\n", (sliceLeft - 1) * i + sliceRight + 1);
                }
                zeros += (sliceLeft - 1) * i + sliceRight + 1;
            } else {
                if (verbose) {
                    printf("zeros += %ld\n", sliceLeft * i);
                }
                zeros += sliceLeft * i;
            }
            if (verbose) {
                printf("zeros after: %ld\n", zeros);
            }
        }
}

long countZeros(long n)
{
    ll count = 0;

    if (n == 0)
        return 1;

    while (n > 0)
    {
        if (n % 10 == 0)
            count++;
        n /= 10;
    }
    return count;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);
    long n, m;

    while (cin >> m >> n)
    {
        if (m < 0)
            break;
        else {
            long zeros = countZeros(m);
            long lower = countZerosUpTo(m, true);
            long upper = countZerosUpTo(n, true);
            cout << zeros + upper - lower << nl;
        }
    }

    return 0;
}