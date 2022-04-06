#include <bits/stdc++.h>
using namespace std;
const int N = 6e3 + 5, mod = 1e9 + 7;
int n, a[N], b[N], p[N], fac[N], inv[N], pre, cur = 1, f[2][N], tot, ans;
bool vis[N];
int C(int n, int m) {
  return n < m ? 0 : 1ll * fac[n] * inv[m] % mod * inv[n - m] % mod;
}
signed main() {
  scanf("%d", &n), fac[0] = inv[0] = inv[1] = 1;
  for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
  for (int i = 1; i <= n; i++) scanf("%d", &b[i]), p[a[i]] = b[i];
  for (int i = 2; i <= 2 * n + 1; i++) inv[i] = 1ll * inv[mod % i] * (mod - mod / i) % mod;
  for (int i = 1; i <= 2 * n + 1; i++)
    fac[i] = 1ll * fac[i - 1] * i % mod, inv[i] = 1ll * inv[i - 1] * inv[i] % mod;
  f[cur][0] = 1;
  for (int x = 1; x <= n; x++)
    if (!vis[x]) {
      int sz = 0;
      for (int i = x; !vis[i]; i = p[i]) vis[i] = 1, sz++;
      swap(cur, pre), fill(f[cur], f[cur] + 2 + tot, 0);
      if (sz == 1)
        for (int i = 0; i <= tot + 1; i++) f[cur][i] = (f[pre][i] + (i ? f[pre][i - 1] : 0)) % mod;
      else
        for (int i = 0; i <= tot; i++)
          for (int j = 0; j <= sz; j++) f[cur][i + j] = (f[cur][i + j] + 1ll * f[pre][i] * (C(2 * sz - j, j) + C(2 * sz - j - 1, j - 1)) % mod) % mod;
      tot += sz;
    }
  for (int i = 0; i <= n; i++)
    ans = (ans + 1ll * (i & 1 ? mod - 1 : 1) * f[cur][i] % mod * fac[n - i] % mod) % mod;
  printf("%d\n", ans);
  return 0;
}