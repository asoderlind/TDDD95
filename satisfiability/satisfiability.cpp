#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

// Begin template code

typedef long long ll;
typedef long double ld;

#define rep(i, a, b) for (int i = a; i < b; ++i)

bool DEBUG = false;

constexpr char nl = '\n';
constexpr ll INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 998244353;
constexpr ld EPS = 1e-9L;

// end template code

// Parse a clause and update the positive and negative bitmasks
void parse(int& pos, int& neg, string it) {
  if (it[0] == '~') {
    neg |= 1 << (stoi(it.substr(2)) - 1);
  } else {
    pos |= 1 << (stoi(it.substr(1)) - 1);
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(NULL);
  std::cout.tie(NULL);
  int numTestCases;
  cin >> numTestCases;
  while (numTestCases--) {
    int numVariables, numClauses;
    cin >> numVariables >> numClauses;
    string line;
    getline(cin, line);
    vector<pair<int, int>> clauses;
    while (numClauses--) {
      getline(cin, line);
      istringstream in(line);
      int pos = 0;
      int neg = 0;
      in >> line;
      parse(pos, neg, line);
      while (in >> line) {
        in >> line;
        parse(pos, neg, line);
      }
      clauses.push_back({pos, neg});
    }

    // Check all possible assignments
    bool satisfiable = false;
    for (int assignment = 0; assignment < 1 << numVariables && !satisfiable; assignment++) {
      bool ok = true;
      // Check if all clauses are satisfied
      for (auto [pos, neg] : clauses) {
        ok &= ((pos & assignment) || (neg & ~assignment));
      }
      satisfiable |= ok;
    }

    cout << (satisfiable ? "" : "un") << "satisfiable" << nl;
  }

  return 0;
}