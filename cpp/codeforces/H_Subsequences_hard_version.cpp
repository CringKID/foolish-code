#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
using ll = long long;
using Pii = pair <int, int>;
using Pll = pair <ll, ll>;
const int kMaxN = 155, kMod = 1e9 + 7, kInf = 1e9;

char str[kMaxN];
ll dp[kMaxN][kMaxN], pre[55], n, k;
//#define contest
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);
#ifdef contest
  freopen (, , stdin);
  freopen (, , stdout);
#endif

  for ( ; cin >> n >> k; ) {
    cin >> str + 1, memset (pre, 0, sizeof (pre)), dp[0][0] = 1ll;
    for (int i = 1; i <= strlen (str + 1); i++) {
      dp[i][0] = 1ll;
      for (int j = 1; j <= i; j++) {
        dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
        int cur = pre[str[i] - 'a'];
        (cur && j >= i - cur ? (dp[i][j] -= dp[cur - 1][cur - (i - j)]) : 0);
        dp[i][j] = min (dp[i][j], k);
      }
      pre[str[i] - 'a'] = i;
    }
    ll ans = 0;
    for (int i = 0; i <= n; i++) {
      ans += min (k, dp[n][i]) * i;
      k -= dp[n][i];
      if (k <= 0) {
        break;
      }
    }
    cout << (k > 0 ? -1 : ans) << '\n';
  }
  return 0;
}