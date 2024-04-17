#include <algorithm>
#include <cmath>
#include <iostream>
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

// Define vector struct
struct vec2 {
  int x, y;
  vec2(int x, int y) : x(x), y(y) {}
  vec2 operator-() const { return vec2(-x, -y); }
};

// Define dot product
int dot(vec2 a, vec2 b) { return a.x * b.x + a.y * b.y; }

// Define area of triangle
float area(vec2 a, vec2 b, vec2 c) { return 0.5 * (a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y)); }

// Define angle between vectors
float angle(vec2 a, vec2 b) {
  float dotProduct = dot(a, b);
  float aLength = sqrt(dot(a, a));
  float bLength = sqrt(dot(b, b));
  return acos(dotProduct / (aLength * bLength));
}

float length(vec2 a) { return sqrt(dot(a, a)); }

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(NULL);
  std::cout.tie(NULL);

  // read input
  int remainingTestCases, currentTestCase = 1;
  cin >> remainingTestCases;
  while (remainingTestCases--) {
    int x1, x2, x3, y1, y2, y3;
    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
    vec2 a(x1, y1), b(x2, y2), c(x3, y3);
    vec2 ab(x2 - x1, y2 - y1), bc(x3 - x2, y3 - y2), ca(x1 - x3, y1 - y3);
    float a1 = area(a, b, c);
    cout << "Case #" << currentTestCase << ": ";
    if (a1 == 0) {
      cout << "not a triangle" << nl;
    } else {
      // lengths of sides
      float abLength = length(ab), bcLength = length(bc), caLength = length(ca);
      string sideType =
          (abLength == bcLength || bcLength == caLength || abLength == caLength) ? "isosceles" : "scalene";
      // angles
      float angleA = angle(ab, -ca), angleB = angle(bc, -ab), angleC = angle(ca, -bc);
      string angleType = (angleA == float(M_PI_2) || angleB == float(M_PI_2) || angleC == float(M_PI_2)) ? "right"
                         : (angleA < M_PI_2 && angleB < M_PI_2 && angleC < M_PI_2)                       ? "acute"
                                                                                                         : "obtuse";
      // output
      cout << sideType << " " << angleType << " triangle" << nl;
    }
    currentTestCase++;
  }

  return 0;
}