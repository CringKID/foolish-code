#include <iostream>
#include <vector>

using namespace std;
using ll = long long;
const int kMaxN = 5e3 + 5, kMod = 998244353;

ll quick_pow (ll a, ll b) {
  return b ? quick_pow (a * a % kMod, b / 2) * (b % 2 ? a : 1) % kMod : 1;
}
ll n, m, ans[kMaxN], cnt[kMaxN], inv[kMaxN], dp[kMaxN];
int main () {
  cin >> n >> m;
  fill (ans, ans + n + 1, 1), fill (dp, dp + n + 2, 1);
  for (int i = 0; i < n; i++) {
    dp[i + 1] = dp[i] * (i + 1) % kMod;
  }
  for (int i = 0; i <= n; i++) {
    inv[i] = quick_pow (dp[i], kMod - 2);
  }
  for (int i = 0; i < n; i++) {
    cnt[i % m]++;
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (i + 1 < cnt[j]) {
        ans[i] = 0;
      } else {
        ans[i] = ans[i] * dp[i + 1] % kMod * inv[i + 1 - cnt[j]] % kMod;
      }
    }
    ans[i] = ans[i] * inv[i + 1] % kMod;
    for (int j = 0; j < i; j++) {
      ans[i] = (ans[i] - ans[j] * inv[i - j] % kMod + kMod) % kMod;
    }
    cout << ans[i] << endl;
  }
}