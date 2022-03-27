#include <iostream>
#include <algorithm>

using namespace std;
const int kMaxN = 5e3 + 5, kMod = 998244353;

int n, m, dp[kMaxN][kMaxN];
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n >> m;
  dp[1][1] = 1;
  if (m + 1 <= n) {
    dp[m + 1][m + 1] = -1;
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < n; j++) {
      if (i + 1 <= n && j + 1 <= n) {
        dp[i + 1][j + 1] = (dp[i + 1][j + 1] + dp[i][j]) % kMod;
      }
      if (i + j <= n) {
        dp[i][i + j] = (dp[i][i + j] + dp[i][j]) % kMod;
        if (i + j + m + 1 <= n) {
          dp[i + m + 1][i + j + m + 1] = (dp[i + m + 1][i + j + m + 1] + kMod - dp[i][j]) % kMod;
        }
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    cout << dp[i][n] << '\n';
  }
  return 0;
}