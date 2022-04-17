#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;
using Pii = pair <ll, ll>;
using Pll = pair <ll, ll>;
const ll kMaxN = 1ll << 18, kMod = 998244353, kInf = 1e9;

ll rec[kMaxN], d[25], arr[25], dp1[kMaxN], dp2[kMaxN];
ll solve (ll x) {
  ll cnt = 0;
  for (ll i = 0; i <= 17; i++) {
    if (x >> i & 1ll) {
      cnt++;
    }
  }
  return cnt;
}
//#define contest
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);
#ifdef contest
  freopen (, , stdin);
  freopen (, , stdout);
#endif

  ll n, m; rec[0] = 1, cin >> n >> m;
  for (ll i = 1; i <= n; i++) {
    rec[i] = rec[i - 1] * i % kMod;
  }
  for (ll i = 0; i < n; i++) {
    cin >> d[i];
  }
  for (ll i = 1; i <= n; i++) {
    if (i & 1ll) {
      arr[i] = rec[i - 1];
    } else {
      arr[i] = (kMod - rec[i - 1]) % kMod;
    }
  }
  for (ll k = 0; k < (1ll << n); k++) {
    ll val = 1;
    for (ll i = 0; i < n; i++) {
      if ((k >> i) & 1) {
        ll gcd = __gcd (val, d[i]);
        if (val / gcd * 1.0 * d[i] > 2E18) {
          val = m + 1; break;
        }
        val = val / gcd * d[i];
      }
    }
    dp1[k] = (m / val % kMod * arr[solve (k)]) % kMod;
    if (dp1[k] < 0) {
      dp1[k] = (dp1[k] + kMod) % kMod;
    }
  }
  dp2[0] = 1;
  for (ll k = 1; k < (1ll << n); k++) {
    ll cur = k & (~(k & -k));
    for (ll i = cur; ; i = (i - 1) & cur) {
      dp2[k] = (dp2[k] + dp1[i | (k & -k)] * dp2[cur ^ i]) % kMod;
      if (!i) {
        break;
      }
    }
  }
  cout << dp2[(1 << n) - 1] << '\n';
  return 0;
}