#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;
typedef long double ld;

#define rep(i, a, b) for (int i = a; i < b; ++i)

bool DEBUG = true;

constexpr char nl = '\n';
constexpr ll INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 998244353;
constexpr ld EPS = 1e-9L;

// ------------------------------------------- //

const vector<char> IMPOSSIBLE = {'I', 'M', 'P', 'O', 'S',
                                 'S', 'I', 'B', 'L', 'E'};

vector<char> reconstructedString(int outputStringLen, int numSuffixes) {
  vector<char> output;
  output.assign(outputStringLen, '-');
  bool impossible = false;
  int pos;
  string suffix;
  for (int i = 0; i < numSuffixes; i++) {
    cin >> pos >> suffix;
    pos--;
    if (DEBUG) cout << "pos: " << pos << ", suffix: " << suffix << nl;
    bool hasWildcard = false;
    // check if suffix is impossible
    for (int p = pos; p < pos + suffix.size(); p++) {
      if (suffix[p - pos] == '*') {
        hasWildcard = true;
        break;
      }
      if (output[p] != '-' && output[p] != suffix[p - pos]) {
        impossible = true;
        break;
      }
      // fill in the suffix
      output[p] = suffix[p - pos];
    }
    if (hasWildcard) {
      // fill in the suffix from the left
      for (int p = outputStringLen - 1; p >= pos; p--) {
        // check if suffix is impossible
        if (suffix[p - outputStringLen + suffix.size()] == '*') {
          break;
        }
        // check if suffix is impossible
        if (output[p] != '-' &&
            output[p] != suffix[p - outputStringLen + suffix.size()]) {
          impossible = true;
          break;
        }
        // fill in the suffix
        output[p] = suffix[p - outputStringLen + suffix.size()];
      }
    }
  }
  // check if suffix is impossible
  for (int i = 0; i < outputStringLen; i++) {
    if (output[i] == '-') {
      impossible = true;
      break;
    }
  }
  return impossible ? IMPOSSIBLE : output;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(NULL);
  std::cout.tie(NULL);

  // read input
  int numTestCases;
  cin >> numTestCases;
  if (DEBUG) cout << "numTestCases: " << numTestCases << nl;
  for (int i = 0; i < numTestCases; i++) {
    int outputStringLen, numSuffixes;
    cin >> outputStringLen >> numSuffixes;
    if (DEBUG)
      cout << "outputStringLen: " << outputStringLen
           << ", numSuffixes: " << numSuffixes << nl;
    vector<char> res = reconstructedString(outputStringLen, numSuffixes);
    for (int j = 0; j < res.size(); j++) {
      cout << res[j];
    }
    cout << nl;
  }
  return 0;
}