#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;
using ll = long long;
const int kMaxN = 1e5 + 5;
const ll kInf = 1e18;

ll dp[kMaxN];
double LOG2 = log (2);
pair <int, int> P[kMaxN];
int n, m, k, s, arr[kMaxN], pos[kMaxN], p, q, mmax[kMaxN][17], mmin[kMaxN][17];
int RMQ (int l, int r) {
  int k = log (r - l + 1) / LOG2;
  return max (mmax[l][k], mmax[r - (1 << k) + 1][k]) - min (mmin[l][k], mmin[r - (1 << k) + 1][k]);
}
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n >> m >> k >> s;
  for (int i = 1; i <= n; i++) {
    cin >> arr[i];
  }
  for (int i = 1; i <= m; i++) {
    cin >> p >> q;
    if (p > q) {
      swap (p, q);
    }
    pos[q] = max (pos[q], p);
  }
  if (!s) {
    int cur = 0, pre = 0, ans = 0;
    for (int i = 1; i <= n; i++) {
      if (pos[i]) {
        P[++cur] = {i, pos[i]};
      }
    }
    sort (P + 1, P + cur + 1);
    for (int i = 1; i <= cur; i++) {
      if (P[i].second <= pre) {
        continue;
      }
      pre = P[i].first, ans++;
    }
    cout << ans * k + k << '\n';
  } else {
    for (int i = 1; i <= n; i++) {
      mmax[i][0] = mmin[i][0] = arr[i];
    }
    for (int j = 1; j <= log (n); j++) {
      for (int i = 1; i + (1 << j) - 1 <= n; i++) {
        mmax[i][j] = max (mmax[i][j - 1], mmax[i + (1 << (j - 1))][j - 1]);
        mmin[i][j] = min (mmin[i][j - 1], mmin[i + (1 << (j - 1))][j - 1]);
      }
    }
    for (int i = 1; i <= n; i++) {
      dp[i] = kInf;
      int x = pos[i];
      for (int j = i - 1; j >= x; j--) {
        dp[i] = min (dp[i], dp[j] + k + 1ll * s * RMQ (j + 1, i));
        x = max (x, pos[j]);
      }
    }
    cout << dp[n] << '\n';
  }
  return 0;
}