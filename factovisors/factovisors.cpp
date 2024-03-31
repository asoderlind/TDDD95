/** TDDD95: Lab X - <name>
 * Author: Axel Söderlind
 * Date:   2024-01-22
 * This problem is about ...
 */
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

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

double factorial(double n) {
  if (n == 0) return 1;
  return n * factorial(n - 1);
}

bool doesDivide(double m, double nFact) { return fmod(nFact, m) == 0; }
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(NULL);
  std::cout.tie(NULL);

  // read input
  double n, m;
  while (cin >> n >> m) {
    if (DEBUG) cout << "n: " << n << ", m: " << m << nl;
    // the question is if m divides n!
    double nFact = factorial(n);
    if (DEBUG) cout << "nFact: " << nFact << nl;
    if (m == 1) {
      cout << m << " divides " << n << "!\n";
    } else if (doesDivide(m, nFact)) {
      cout << m << " divides " << n << "!\n";
    } else {
      cout << m << " does not divide " << n << "!\n";
    }
  }

  return 0;
}