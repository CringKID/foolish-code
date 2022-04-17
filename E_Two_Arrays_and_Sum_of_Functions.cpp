#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;
using Pii = pair <int, int>;
using Pll = pair <ll, ll>;
const int kMaxN = 2e5 + 5, kMod = 998244353, kInf = 1e9;

ll n, arr1[kMaxN], arr2[kMaxN], arr3[kMaxN];
//#define contest
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);
#ifdef contest
  freopen (, , stdin);
  freopen (, , stdout);
#endif

  while (cin >> n) {
    for (int i = 0; i < n; i++) {
      cin >> arr1[i];
    }
    for (int i = 0; i < n; i++) {
      cin >> arr2[i];
    }
    for (int i = 0; i < n; i++) {
      arr3[i] = (n - i) * (i + 1) * arr1[i];
    }
    sort (arr3, arr3 + n), sort (arr2, arr2 + n, [] (ll x, ll y) { return x > y; });
    ll ans = 0;
    for (int i = 0; i < n; i++) {
      (ans += arr3[i] % kMod * arr2[i]) %= kMod;
    }
    cout << ans << '\n';
  }
  return 0;
}