#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cmath>

using namespace std;
using ll = long long;
using Pii = pair <int, int>;
using Pll = pair <ll, ll>;
const int kMaxN = 1e5 + 5, kMod = 1e9 + 7, kInf = 1e9, kDir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
const double kEps = 1e-8, begint = 5.0, mint = 1e-2, maxT = 10000000;

struct Node {
  double x, y, r;
  double angle (double x_, double y_) {
    return r / sqrt((x_ - x) * (x_ - x) + (y_ - y) * (y_ - y));
  }
} node[3];
double calc (double x, double y) {
  double r1 = node[0].angle (x, y), r2 = node[1].angle (x, y), r3 = node[2].angle (x, y);
  return (r1 - r2) * (r1 - r2) + (r3 - r2) * (r3 - r2) + (r1 - r3) * (r1 - r3);
}
void solve (double &x, double &y, double &t, double &ans, double tem) {
  double cur = ans, nx = x, ny = y, dx, dy, val;
  for (int i = 0; i < 4; i++) {
    dx = nx + kDir[i][0] * t, dy = ny + kDir[i][1] * t, val = calc (dx, dy);
    if (val < ans) {
      ans = val, x = dx, y = dy;
    }
  }
  if (fabs (cur - ans) < kEps) {
    t = max (mint * (1.0 * tem / maxT), t / 2);
  }
}
double anneal (double &x, double &y) {
  double ans = 1.0, tem = begint;
  x = (node[0].x + node[1].x + node[2].x) / 3.0, y = (node[0].y + node[1].y + node[2].y) / 3.0;
  for (int i = 1000000; i; i--) {
    solve (x, y, tem, ans, i);
  }
  return ans;
}
//#define contest
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);
#ifdef contest
  freopen (, , stdin);
  freopen (, , stdout);
#endif

  double x, y, r;
  cin >> x >> y >> r, node[0] = {x, y, r};
  cin >> x >> y >> r, node[1] = {x, y, r};
  cin >> x >> y >> r, node[2] = {x, y, r};
  double ans = anneal (x, y);
  if (fabs (ans) < 1e-6) {
    cout << fixed << setprecision (5) << x << ' ' << y << '\n';
  } else {
    cout << '\n';
  }
  return 0;
}