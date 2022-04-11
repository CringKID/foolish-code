#include <iostream>
#include <algorithm>
#include <climits>

using namespace std;
const int kMaxN = 1e4 + 5, kInf = INT_MAX, kDir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

pair <int, int> P[kMaxN];
int n, x[kMaxN], y[kMaxN], ans1 = kInf, ans2;
int calc (int nx, int ny) {
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    ans += abs (nx - x[i]) + abs (ny - y[i]);
  }
  return ans;
}
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> x[i] >> y[i];
    P[i].first = x[i], P[i].second = y[i];
  }
  sort (x + 1, x + n + 1), sort (y + 1, y + n + 1);
  
  if (n & 1) {
    int nx = x[n / 2 + 1], ny = y[n / 2 + 1];
    for (int i = 0; i < 4; i++) {
      int dx = nx + kDir[i][0], dy = ny + kDir[i][1], k = calc (dx, dy);
      if (k < ans1) {
        ans1 = k, ans2 = 1;
      } else if (k == ans1) {
        ans2++;
      }
    }
  } else {
    int nx = x[n / 2 + 1], ny = y[n / 2 + 1], dx = x[n / 2], dy = y[n / 2];
    ans2 = (nx - dx + 1) * (ny - dy + 1), ans1 = calc (nx, ny);
    for (int i = 1; i <= n; i++) {
      if (P[i].first <= nx && P[i].first >= dx && P[i].second <= ny && P[i].second >= dy) {
        ans2--;
      }
    }
  }
  cout << ans1 << ' ' << ans2 << '\n';
  return 0;
}