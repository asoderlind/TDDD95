#include <algorithm>
#include <cmath>
#include <cstdio>
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

// Sieve of Eratosthenes
tuple<vector<int>, int> sieve(int N) {
  vector<int> primes(N);
  int numPrimes = 0;
  vector<bool> not_prime(N, 0);

  primes[numPrimes++] = 2;
  for (int i = 3; i < N; ++i) {
    if (!not_prime[i]) {
      primes[numPrimes++] = i;
      for (int j = i * i; j < N; j += (i << 1)) not_prime[j] = 1;
    }
  }

  return {primes, numPrimes};
}

// Count the number of times p divides n!
int factorialDivisions(int n, const int& p) {
  int count = 0;
  // Count the number of times p divides n!
  while (n) {
    count += n / p;
    n /= p;
  }
  return count;
}

// Count the number of times p divides n
int countDivisions(int& n, const int& p) {
  int count = 0;

  // Divide n by p as long as n is divisible by p
  while (n % p == 0) {
    count++;
    n /= p;
  }

  return count;
}

// Check if m divides n
bool doesDivide(vector<int> primes, int numPrimes, int m, int n) {
  for (int i = 0; i < numPrimes && primes[i] <= m; ++i) {
    if (countDivisions(m, primes[i]) > factorialDivisions(n, primes[i]))
      return false;  // m does not divide n
  }
  // If m is still greater than 1, check if n is greater or equal to m
  if (m > 1) return n >= m;
  return true;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(NULL);
  std::cout.tie(NULL);

  int N = 46341;  // sqrt(2^31)
  auto [primes, numPrimes] = sieve(N);

  // read input
  int n, m;
  while (cin >> n >> m) {
    if (m == 0) {
      cout << "0 does not divide " << n << "!\n";
      continue;
    }
    if (DEBUG) cout << "n: " << n << ", m: " << m << nl;
    if (n >= m || doesDivide(primes, numPrimes, m, n)) {
      cout << m << " divides " << n << "!\n";
    } else {
      cout << m << " does not divide " << n << "!\n";
    }
  }

  return 0;
}