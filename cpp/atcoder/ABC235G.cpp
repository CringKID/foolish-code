#include <iostream>
#include <algorithm>
#include <atcoder/all>

using namespace std;
using namespace atcoder;
using mint = modint998244353;
const int kMaxN = 5e6 + 5;

int n, a, b, c;
mint fac[kMaxN], infac[kMaxN], inv[kMaxN], ans, s1 = 1, s2 = 1, s3 = 1;
mint quickpow (mint x, int y) {
  mint rec = 1;
  for ( ; y; (y & 1 ? rec *= x : 0), x = x * x, y >>= 1) {
  }
  return rec;
}
mint C (int x, int y) {
  return (y < 0 || x < y ? 0 : fac[x] * infac[y] * infac[x - y]);
}
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n >> a >> b >> c, fac[0] = 1;
  for (int i = 1; i <= n; i++) {
    fac[i] = fac[i - 1] * i;
  }
  infac[n] = quickpow (fac[n], 998244351);
  for (int i = n; i >= 1; i--) {
    infac[i - 1] = infac[i] * i;
  }
  for (int i = 0; i <= n; i++) {
    (n - i & 1 ? ans -= C (n, i) * s1 * s2 * s3 : ans += C (n, i) * s1 * s2 * s3);
    s1 = (s1 * 2 - C (i, a)), s2 = (s2 * 2 - C (i, b)), s3 = (s3 * 2 - C (i, c));
  }
  cout << ans.val () << '\n';
  return 0;
}