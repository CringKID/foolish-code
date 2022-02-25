#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
using ll = long long;
const int kMaxN = 3e5 + 5, kMod = 998244353;

ll rec[kMaxN];
int n, m, arr[kMaxN], cop[kMaxN], tree[kMaxN];
ll quickpow (ll base, int index) {
  ll ans = 1;
  for ( ; index; index >>= 1) {
    if (index & 1) {
      ans = ans * base % kMod;
    }
    base = base * base % kMod;
  }
  return ans;
}
void update (int x, int val) {
  for ( ; x <= m; x += x & -x) {
    (tree[x] += val) %= kMod;
  }
}
int query (int x) {
  int ans = 0;
  for ( ; x > 0; x -= x & -x) {
    (ans += tree[x]) %= kMod;
  }
  return ans;
}

int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> arr[i];
    cop[i] = arr[i];
  }
  sort (cop, cop + n), m = unique (cop, cop + n) - cop;
  rec[n] = quickpow (quickpow (2, n), kMod - 2);
  for (int i = n - 1; i >= 0; i--) {
    rec[i] = (rec[i + 1] << 1) % kMod;
  }
  memset (tree, 0, sizeof (tree));
  int ans = 0; ll rate = 1;
  for (int i = 0; i < n; i++) {
    int cur = lower_bound (cop, cop + m, arr[i]) - cop + 1;
    (ans += query (cur) * rate % kMod) %= kMod;
    update (cur, rec[i + 1]);
    rate = (rate << 1) % kMod;
  }
  cout << ans << '\n';
  return 0;
}