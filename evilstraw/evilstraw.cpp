/** TDDD95: Lab X - <name>
 * Author: Axel Söderlind
 * Date:   2024-01-22
 * This problem is about ...
 */
#include <algorithm>
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

bool isShuffledPalindrome(const string& s) {
  vector<int> occurrence(26, 0);
  int odd_count = 0;
  for (char i : s) {
    occurrence[i - 'a']++;
  }
  for (int value : occurrence) {
    if (value % 2 != 0) {
      odd_count++;
    }
  }
  return odd_count <= 1;
}

int getNumSwaps(string s) {
  int stringLen = s.size();
  int result = 0;
  int start = 0, end = stringLen - 1;

  // if string is empty or it is not a palindrome return -1
  if ((stringLen == 0) || (!isShuffledPalindrome(s))) {
    return -1;
  }

  while (end > start) {
    if (s[start] != s[end]) {
      int i = end;  // make an additional iterator from the end

      while (i > start && s[i] != s[start]) {
        --i;
      }

      if (i == start) {
        swap(s[start], s[start + 1]);
        ++result;
      } else {
        while (i < end) {
          swap(s[i], s[i + 1]);
          ++result;
          ++i;
        }
        ++start;
        --end;
      }
    } else {
      ++start;
      --end;
    }
  }
  return result;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(NULL);
  std::cout.tie(NULL);

  // read input
  int numCases;
  cin >> numCases;

  for (int i = 0; i < numCases; ++i) {
    // read input
    string s;
    cin >> s;
    int numSwaps = getNumSwaps(s);
    if (numSwaps == -1) {
      cout << "Impossible" << nl;
    } else {
      cout << numSwaps << nl;
    }
  }

  return 0;
}