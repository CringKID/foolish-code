#include <iostream>
#include <algorithm>

using namespace std;
const int kMaxN = 6e3 + 5, kMod = 1e9 + 7;

bool vis[kMaxN];
int n, a[kMaxN], b[kMaxN], p[kMaxN], fac[kMaxN], inv[kMaxN], pre, cur = 1, dp[2][kMaxN], tot, ans;
int C (int n, int m) {
  return n < m ? 0 : 1ll * fac[n] * inv[m] % kMod * inv[n - m] % kMod;
}
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n, fac[0] = inv[0] = inv[1] = 1;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (int i = 1; i <= n; i++) {
    cin >> b[i], p[a[i]] = b[i];
  }
  for (int i = 2; i <= 2 * n + 1; i++) {
    inv[i] = 1ll * inv[kMod % i] * (kMod - kMod / i) % kMod;
  }
  for (int i = 1; i <= 2 * n + 1; i++) {
    fac[i] = 1ll * fac[i - 1] * i % kMod, inv[i] = 1ll * inv[i - 1] * inv[i] % kMod;
  }
  dp[cur][0] = 1;
  for (int x = 1; x <= n; x++) {
    if (!vis[x]) {
      int siz = 0;
      for (int i = x; !vis[i]; i = p[i]) {
        vis[i] = true, siz++;
      }
      swap (cur, pre), fill (dp[cur], dp[cur] + 2 + tot, 0);
      if (siz == 1) {
        for (int i = 0; i <= tot + 1; i++) {
          dp[cur][i] = (dp[pre][i] + (i ? dp[pre][i - 1] : 0)) % kMod;
        }
      } else {
        for (int i = 0; i <= tot; i++) {
          for (int j = 0; j <= siz; j++) {
            dp[cur][i + j] = (dp[cur][i + j] + 1ll * dp[pre][i] * (C (2 * siz - j, j) + C (2 * siz - j - 1, j - 1)) % kMod) % kMod;
          }
        }
      }
      tot += siz;
    }
  }
  for (int i = 0; i <= n; i++) {
    ans = (ans + 1ll * (i & 1 ? kMod - 1 : 1) * dp[cur][i] % kMod * fac[n - i] % kMod) % kMod;
  }
  cout << ans << '\n';
  return 0;
}