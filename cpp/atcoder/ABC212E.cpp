#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
const int kMaxN = 5e3 + 5, kMod = 998244353;

pair <int, int> edge[kMaxN << 1];
int n, m, k, head[kMaxN], tot, dp[kMaxN][kMaxN];
void add (int from, int to) {
  edge[++tot] = {to, head[from]}, head[from] = tot;
}
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);  

  cin >> n >> m >> k;
  for (int i = 1, from, to; i <= m; i++) {
    cin >> from >> to;
    add (from, to), add (to, from);
  }
  memset (dp, 0, sizeof (dp)), dp[1][0] = 1;
  for (int i = 1; i <= k; i++) {
    int cur = 0;
    for (int j = 1; j <= n; j++) {
      cur = (cur + dp[j][i - 1]) % kMod;
    }
    for (int j = 1; j <= n; j++) {
      dp[j][i] = (cur - dp[j][i - 1] + kMod) % kMod;
      for (int k = head[j]; k; k = edge[k].second) {
        int to = edge[k].first;
        dp[j][i] = (dp[j][i] - dp[to][i - 1] + kMod) % kMod;
      }
    }
  }
  cout << dp[1][k] << '\n';
  return 0;
}