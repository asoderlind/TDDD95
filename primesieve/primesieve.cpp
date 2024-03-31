/**
 * TDDD95: Lab 3.8 - primesieve
 * Author: Axel Söderlind
 * Date:   2024-03-31
 *
 * This program implements the Sieve of Eratosthenes algorithm to identify all
 * prime numbers up to a specified limit. It finds prime numbers up
 * to a given number n and processes queries to determine if specific numbers
 * are prime.
 *
 * The program's core is the sieve function, which marks non-prime numbers in a
 * boolean vector. A query part then checks if numbers are prime based on this
 * vector.
 *
 * Complexity:
 * Time Complexity: O(n log log n) for constructing the sieve.
 * Space Complexity: O(n) for storing prime number indicators up to n.
 */

#include <iostream>
#include <tuple>
#include <vector>

using namespace std;

typedef long long ll;
typedef long double ld;
bool DEBUG = false;

constexpr char nl = '\n';
constexpr ll INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 998244353;
constexpr ld EPS = 1e-9L;

/// @brief Implements the Sieve of Eratosthenes to find all prime numbers up to
/// n.
/// @param n The upper limit to find primes up to.
/// @return A tuple containing a boolean vector indicating prime status for
/// numbers up to n, and the total count of primes found.
tuple<vector<bool>, int> sieve(int n) {
  vector<bool> isPrime(n + 1, true);
  isPrime[0] = isPrime[1] = false;  // 0 and 1 are not prime numbers
  int totalPrimes = 0;

  for (int i = 2; i * i <= n; ++i) {
    if (isPrime[i]) {
      for (int j = i * i; j <= n; j += i) {
        isPrime[j] = false;
      }
    }
  }

  // Count prime numbers
  for (int i = 2; i <= n; ++i) {
    if (isPrime[i]) {
      ++totalPrimes;
    }
  }

  return {isPrime, totalPrimes};
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);

  int n, q;
  cin >> n >> q;  // Read upper limit n and number of queries q
  if (DEBUG) cout << "n: " << n << ", q: " << q << nl;

  auto [isPrime, totalPrimes] = sieve(n);
  cout << totalPrimes << nl;  // Output total number of primes up to n

  // Process each query
  while (q--) {
    int query;
    cin >> query;
    if (DEBUG) cout << "Query: " << query << nl;
    cout << isPrime[query] << nl;  // Output 1 if prime, 0 otherwise
  }

  return 0;
}
