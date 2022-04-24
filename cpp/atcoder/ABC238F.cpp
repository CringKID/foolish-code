#include <iostream>
#include <algorithm>
#include <atcoder/all>
#include <cstring>

using namespace std;
using namespace atcoder;
using ll = long long;
using mint = modint998244353;
using Mint = modint1000000007;
using Pii = pair <int, int>;
using Pll = pair <ll, ll>;
const int kMaxN = 355, kMod = 1e9 + 7, kInf = 1e9;

int n, k, arr1[kMaxN], arr2[kMaxN];
mint map[kMaxN], dp[kMaxN][kMaxN], now[kMaxN][kMaxN], ans;
//#define contest
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);
#ifdef contest
  freopen (, , stdin);
  freopen (, , stdout);
#endif

  cin >> n >> k;
  for_each (arr1, arr1 + n, [] (int &x) { cin >> x; });
  for_each (arr2, arr2 + n, [] (int &x) { cin >> x; });
  for (int i = 0; i < n; i++) {
    map[arr1[i] - 1] = arr2[i] - 1;
  }
  dp[0][n] = 1;
  for (int i = 0; i < n; i++) {
    memset (now, 0, sizeof (now));
    for (int x = 0; x <= k; x++) {
      for (int y = 0; y <= n; y++) {
        (x < k && map[i].val () < y ? (now[x + 1][y] += dp[x][y]) : 0);
        now[x][(y < map[i].val () ? y : map[i].val ())] += dp[x][y];
      }
    }
    swap (dp, now);
  }
  for_each (dp[k], dp[k] + n + 1, [] (mint x) { ans += x; });
  cout << ans.val () << '\n';
  return 0;
}