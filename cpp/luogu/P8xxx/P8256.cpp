#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
const int kMaxN = 405, kMod = 1e9 + 7;

char str[kMaxN], tmp[kMaxN];
int q, n, m, ans, dp[kMaxN][kMaxN][kMaxN];
int DP (int dep, int cur, int x, int y) {
  if (dep > n) {
    return cur == m && !x && !y;
  } else if (~dp[dep][cur][x]) {
    return dp[dep][cur][x];
  }
  long long val = 0;
  if (str[dep] == '-') {
    if (x) {
      val += DP (dep + 1, cur, x - 1, y);
    }
    if (y) {
      val += DP (dep + 1, cur, x, y - 1);
    }
  } else {
    val += DP (dep + 1, cur, x, y + 1);
    if (!cur && !y) {
      val += DP (dep + 1, 0, x + 1, y);
    }
    if (str[dep] == tmp[cur + 1] && !y) {
      val += DP (dep + 1, cur + 1, x, y);
    }
  }
  return dp[dep][cur][x] = val % kMod;
}
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> q;
  while (q--) {
    cin >> n >> m >> str + 1 >> tmp + 1;
    memset (dp, -1, sizeof (dp));
    ans = DP (1, 0, 0, 0);
    cout << ans << '\n';
  }
  return 0;
}