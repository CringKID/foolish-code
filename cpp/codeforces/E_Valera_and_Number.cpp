#include <bits/stdc++.h>

using namespace std;
using ll = long long;
const int kMaxN = 355;

int x, k;
double p, cur, dp[kMaxN][kMaxN];
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> x >> k >> p;
  p /= 100;
  cur = 1.0 - p;
  for (int i = 0; i <= k; i++) {
    for (int j = x + i; !(j & 1); j >>= 1) {
      dp[0][i]++;
    }
  }
  for (int i = 0; i < k; i++) {
    for (int j = 0; j <= k; j++) {
      if (j) {
        dp[i + 1][j - 1] += cur * dp[i][j];
      }
      if (j << 1 <= k) {
        dp[i + 1][j << 1] += p * (dp[i][j] + 1);
      }
    }
  }
  cout << fixed << setprecision (13) << dp[k][0] << '\n';

  return 0;
}