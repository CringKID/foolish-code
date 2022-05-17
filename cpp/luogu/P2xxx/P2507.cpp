#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;
using ll = long long;
const int kN = 1e5 + 5;

ll n, f[kN], a[kN], b[kN];
ll sol (ll x, ll y) {
  return x != y ? abs (x - y) : 123543657;
}
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i] >> b[i];
  }
  sort (a + 1, a + n + 1), sort (b + 1, b + n + 1);
  if (a[1] == b[1] && n == 1) {
    cout << -1 << '\n';
    return 0;
  }
  f[1] = sol (a[1], b[1]), f[2] = min(f[1] + sol (a[2], b[2]), sol (a[1], b[2]) + sol (a[2], b[1]));
  for (int i = 3; i <= n; i++) {
    f[i] = f[i - 1] + sol (a[i], b[i]);
    f[i] = min (f[i], f[i - 2] + sol (a[i], b[i - 1]) + sol (a[i - 1], b[i]));
    f[i] = min (f[i], f[i - 3] + sol (a[i], b[i - 2]) + sol (a[i - 2], b[i]) + sol (a[i - 1], b[i - 1]));
    f[i] = min (f[i], f[i - 3] + sol (a[i], b[i - 1]) + sol (a[i - 1], b[i - 2]) + sol (a[i - 2], b[i]));
    f[i] = min (f[i], f[i - 3] + sol (a[i], b[i - 2]) + sol (a[i - 1], b[i]) + sol (a[i - 2], b[i - 1]));
  }
  cout << f[n] << '\n';
  return 0;
}
