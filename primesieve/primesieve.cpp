/** TDDD95: Lab 3.8 - primesieve
 * Author: Axel Söderlind
 * Date:   2024-03-31
 * This problem is about finding all prime numbers up to a given number.
 * We use the sieve of Eratosthenes to find all prime numbers up to a given
 * number. We then answer the queries, if it is a prime number or not.
 *
 * Time complexity O(n log log n) to construct the sieve
 * Space complexity O(n)
 */
#include <algorithm>
#include <iostream>
#include <tuple>
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

/// @brief Sieve of Eratosthenes, find all prime numbers up to n
/// @param n the number to find all prime numbers up to
/// @return a tuple with a vector of booleans where true means prime and false
/// means not prime, and the total number of prime numbers up to n
tuple<vector<bool>, int> sieve(int n) {
  int total = 0;
  vector<bool> res(n + 1, true);
  res[0] = res[1] = false;  // 0 and 1 are not prime

  // mark all multiples of prime numbers as not prime
  for (int i = 2; i * i <= n; i++) {
    if (res[i]) {
      for (int j = i * i; j <= n; j += i) {
        res[j] = false;
      }
    }
  }

  // count the number of prime numbers
  for (int i = 2; i <= n; i++) {
    if (res[i]) {
      total++;
    }
  }
  return {res, total};
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(NULL);
  std::cout.tie(NULL);

  // read input
  int n, q;
  cin >> n >> q;
  if (DEBUG) cout << "n: " << n << ", q: " << q << nl;
  auto [res, total] = sieve(n);
  cout << total << nl;
  for (int i = 0; i < q; i++) {
    int query;
    cin >> query;
    if (DEBUG) cout << "query: " << query << nl;
    if (res[query]) {
      cout << "1\n";
    } else {
      cout << "0\n";
    }
  }

  return 0;
}