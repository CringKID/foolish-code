#include <iostream>
#include <algorithm>
#include <map>

using namespace std;
using ll = long long;
using Pii = pair <int, int>;
using Pll = pair <ll, ll>;
const int kMaxN = 1e5 + 5, kMod = 1e9 + 7, kInf = 1e9;

int n, m, k, tot;
ll arr[kMaxN], ans = 1;
map <int, int> map1;
map <pair <int, int>, bool> map2;
int quickpow (int base, int index) {
  int ans = 1;
  for ( ; index; base = 1ll * base * base % kMod, index >>= 1) {
    if (index & 1) {
      ans = 1ll * ans * base % kMod;
    }
  }
  return ans;
}
//#define contest
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);
#ifdef contest
  freopen (, , stdin);
  freopen (, , stdout);
#endif

  cin >> n >> m >> k;
  for (int i = 1, x, y, now; i <= k; i++) {
    cin >> x >> y;
    if (map2[{x, y}]) {
      continue;
    } else {
      map2[{x, y}] = true;
    }
    now = map1[x];
    if (!now) {
      map1[x] = ++tot, now = tot;
      arr[now] = ((1ll + 1ll * n) * n / 2) % kMod;
    }
    arr[now] = (arr[now] - 1ll * y + kMod) % kMod;
  }
  for (int i = 1; i <= tot; i++) {
    (ans *= arr[i]) %= kMod;
  }
  (ans *= quickpow (((1ll + 1ll * n) * n / 2) % kMod, m - tot)) %= kMod;
  cout << ans << '\n';
  return 0;
}