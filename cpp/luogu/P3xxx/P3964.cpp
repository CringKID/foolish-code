#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;
const int kMaxN = 1e6 + 5;

ll n, px[kMaxN], py[kMaxN], sumx[kMaxN], sumy[kMaxN], ans = LLONG_MAX;
struct Node {
  int x, y, idx;
} p[kMaxN];
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n;
  for (int i = 1, x, y; i <= n; i++) {
    cin >> x >> y;
    p[i] = {x + y, x - y, i};
  }
  sort (p + 1, p + n + 1, [&] (Node p1, Node p2) { return p1.x < p2.x; });
  for (int i = 1; i <= n; i++) {
    px[p[i].idx] = i;
    sumx[i] = sumx[i - 1] + p[i].x;
  }
  sort (p + 1, p + n + 1, [&] (Node p1, Node p2) { return p1.y < p2.y; });
  for (int i = 1; i <= n; i++) {
    py[p[i].idx] = i;
    sumy[i] = sumy[i - 1] + p[i].y;
  }
  sort (p + 1, p + n + 1, [&] (Node p1, Node p2) { return p1.idx < p2.idx; });
  for (int i = 1, cur; i <= n; i++) {
    ans = min (ans, px[i] * p[i].x - sumx[px[i]] + (sumx[n] - sumx[px[i]]) - (n - px[i]) * p[i].x + py[i] * p[i].y - sumy[py[i]] + (sumy[n] - sumy[py[i]]) - (n - py[i]) * p[i].y);
  }
  cout << ans / 2 << '\n';
  return 0;
}