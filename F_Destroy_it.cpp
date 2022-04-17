#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;
using Pii = pair <ll, ll>;
using Pll = pair <ll, ll>;
const ll kMaxN = 2e5 + 5, kMod = 10, kInf = 1e9;

ll n;
ll dp[kMaxN][kMod];
//#define contest
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);
#ifdef contest
  freopen (, , stdin);
  freopen (, , stdout);
#endif

  for (ll i = 0; i <= 9; i++) {
    for (ll j = 0; j <= 9; j++) {
      dp[i][j] = -1;
    }
  }
  cin >> n, dp[0][0] = 0;
  for (ll k = 1; k <= n; k++) {
    ll num, l1 = 0, l2 = 0, l3 = 0, c1[5] = {0}, c2 = 0, c3 = 0, c, v; cin >> num;
    for (ll i = 1; i <= num; i++) {
      cin >> c >> v;
      if (c == 1) {
        if (l1 == 3) {
          ll x = 1;
          if (c1[x] > c1[2]) {
            x = 2;
          }
          if (c1[x] > c1[3]) {
            x = 3;
          }
          c1[x] = max (c1[x], v);
        } else {
          c1[++l1] = v;
        }
      } else if (c == 2) {
        l2 = 1, c2 = max (c2, v);
      } else if (c == 3) {
        l3 = 1, c3 = max (c3, v);
      }
    }
    sort (c1 + 1, c1 + 4);
    ll maxv = max (c1[3], max (c2, c3)), n1 = c1[3], n2 = c1[2];
    n2 = max (n2, c2);
    if (n2 > n1) {
      swap (n1, n2);
    }
    ll n3 = c1[1] + c1[2] + c1[3];
    for (ll i = 0; i <= 9; i++) {
      dp[k][i] = dp[k - 1][i];
    }
    for (ll i = 0; i <= 9; i++) {
      if (dp[k - 1][i] != -1) {
        if (l1 + l2 + l3 >= 1) {
          dp[k][(i + 1) % kMod] = max (dp[k][(i + 1) % kMod], dp[k - 1][i] + maxv + (i + 1 >= 10) * maxv);
        }
        if (l1 + l2 >= 2) {
          dp[k][(i + 2) % kMod] = max (dp[k][(i + 2) % kMod], dp[k - 1][i] + n1 + n2 + (i + 2 >= 10) * n1);
        }
        if (l1 >= 3) {
          dp[k][(i + 3) % kMod] = max (dp[k][(i + 3) % kMod], dp[k - 1][i] + n3 + (i + 3 >= 10) * c1[3]);
        }
      }
    }
  }
  ll ans = -1;
  for (ll i = 0; i <= 9; i++) {
    ans = max (dp[n][i], ans);
  }
  cout << ans << '\n';
  return 0;
}