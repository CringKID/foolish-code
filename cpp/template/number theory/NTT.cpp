#include <bits/stdc++.h>
using namespace std;
#define ll long long
inline void swap(ll &x, ll &y) { x ^= y, y ^= x, x ^= y; }
const int maxn = 3e6 + 5, mod = 998244353, sum = 332748118;
inline int read() {
  register char ch = getchar();
  register int X = 0;
  register bool flag = 1;
  while ((ch < '0' || ch > '9') && ch != '-') ch = getchar();
  if (ch == '-') flag = 0, ch = getchar();
  while (ch >= '0' && ch <= '9') X = (X << 1) + (X << 3) + (ch ^ 48), ch = getchar();
  return flag ? X : ~(X - 1);
}
int n, m, limit = 1, l, r[maxn];
ll a[maxn], b[maxn];
inline ll quickpow(ll a, ll b) {
  ll ans = 1;
  while (b) {
    if (b & 1) ans = (ans * a) % mod;
    a = a * a % mod, b >>= 1;
  }
  return ans % mod;
}
inline void NTT(ll *tmp, int opt) {
  for (register int i = 0; i < limit; i++)
    if (i < r[i]) swap(tmp[i], tmp[r[i]]);
  for (register int mid = 1; mid < limit; mid <<= 1) {
    ll num = quickpow(opt == 1 ? 3 : sum, (mod - 1) / (mid << 1));
    for (register int i = 0; i < limit; i += (mid << 1)) {
      for (register int x, y, j = 1, k = 0; k < mid; k++, j = j * num % mod) {
        x = tmp[i + k], y = j * tmp[i + k + mid] % mod;
        tmp[i + k] = (x + y) % mod, tmp[i + k + mid] = (x - y + mod) % mod;
      }
    }
  }
}
int main() {
  n = read(), m = read();
  for (register int i = 0; i <= n; i++) a[i] = (read() + mod) % mod;
  for (register int i = 0; i <= m; i++) b[i] = (read() + mod) % mod;
  while (limit <= n + m) limit <<= 1, l++;
  for (register int i = 0; i < limit; i++) r[i] = (r[i >> 1] >> 1) | ((i & 1) << l - 1);
  NTT(a, 1), NTT(b, 1);
  for (register int i = 0; i < limit; i++) a[i] = a[i] * b[i] % mod;
  NTT(a, -1);
  ll pos = quickpow(limit, mod - 2);
  for (register int i = 0; i <= n + m; i++) printf("%lld ", a[i] * pos % mod);
  return 0;
}