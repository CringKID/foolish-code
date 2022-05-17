#include <iostream>
#include <algorithm>
#include <atcoder/all>

using namespace std;
using namespace atcoder;
using ll = long long;
using mint = modint998244353;
const int kMaxN = 1e7 + 5, kMod = 998244353;

mint fac[kMaxN], nfac[kMaxN], ans;
mint C (int n, int m) {
  return ((n - m >= 0 && n >= 0 && m >= 0) ? fac[n] * nfac[m] * nfac[n - m] : 0);
}
mint solve (int n, int x) {
  return (((n + x) & 1) ? 0 : C (n, (n + x) / 2));
}
mint solve (int n, int x, int y) {
  return solve (n, x + y) * solve (n, x - y);
}
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  int n, x, y, z; cin >> n >> x >> y >> z;
  fac[0] = 1, nfac[1] = 1;
  for (int i = 1; i <= n; i++) {
    fac[i] = fac[i - 1] * i;
  }
  for (int i = 2; i <= n; i++) {
    nfac[i] = kMod - kMod / i * nfac[kMod % i];
  }
  nfac[0] = 1;
  for (int i = 1; i <= n; i++) {
    nfac[i] = nfac[i - 1] * nfac[i];
  }
  for (int i = 0; i <= n; i++) {
    ans += solve (i, x) * C (n, i) * solve (n - i, y, z);
  }
  cout << ans.val () << '\n';
  return 0;
}