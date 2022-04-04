#include <iostream>
#include <algorithm>
#include <set>

using namespace std;
using ll = long long;
const int kMaxN = 5e4 + 5, kMod = 998244353;

set <ll> s;
ll n, arr3[kMaxN], arr2[kMaxN], m, fac[kMaxN], inv[kMaxN], cnt[kMaxN], g[kMaxN], inv2[kMaxN], arr1[kMaxN];
ll quick_pow (ll base, ll index) {
  ll rec = 1;
  while (index) {
    if (index & 1) {
      rec = rec * base % kMod;
    }
    base = base * base % kMod;
    index >>= 1;
  }
  return rec;
}
ll C (ll n, ll m) {
  if (n < 0 || m < 0 || n < m) {
    return 0;
  }
  return fac[n] * inv[m] % kMod * inv[n - m] % kMod;
}
ll solve (ll val, ll cur) {
  ll rec = 0;
  rec = (C (n, cur) - C (n - val, cur) + kMod) % kMod;
  rec = (rec * inv2[cur]) % kMod;
  return rec;
}
ll func (ll cur) {
  ll rec = 0;
  for (ll i = 1; i <= arr1[0]; i++) {
    ll val = arr1[i];
    rec = (rec + g[val] * solve (val, cur) % kMod) % kMod;
  }
  return rec;
}
int main () {
  fac[0] = inv[0] = 1;
  for (ll i = 1; i <= 5e4; i++) {
    fac[i] = fac[i - 1] * i % kMod;
  }
  for (ll i = 1; i <= 5e4; i++) {
    inv[i] = quick_pow (fac[i], kMod - 2);
  }
  cin >> n;
  for (int i = 1; i <= 5e4; i++) {
    inv2[i] = quick_pow (C (n, i) % kMod, kMod - 2);
  }
  for (ll i = 1; i <= n; i++) {
    cin >> arr3[i];
    arr2[++m] = arr3[i];
  }
  sort (arr2 + 1, arr2 + m + 1);
  m = unique (arr2 + 1, arr2 + m + 1) - arr2 - 1;
  for (ll i = 1; i <= n; i++) {
    arr3[i] = lower_bound (arr2 + 1, arr2 + m + 1, arr3[i]) - arr2;
    cnt[arr3[i]]++;
  }
  for (ll i = 1; i <= m; i++) {
    g[cnt[i]]++;
  }
  for (ll i = 1; i <= n; i++) {
    if (!g[i]) {
      continue;
    }
    arr1[++arr1[0]] = i;
  }
  for (ll i = 1; i <= n; i++) {
    cout << func (i) << '\n';
  }
  return 0;
}