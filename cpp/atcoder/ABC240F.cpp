#include <iostream>
#include <algorithm>
#include <climits>

using namespace std;
using ll = long long;

int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  int test; cin >> test;
  for (int i = 0; i < test; ++i) {
    int n, m; cin >> n >> m;
    ll res = LLONG_MIN, a = 0, b = 0;
    for (int i = 1; i <= n; i++) {
      ll x, y; cin >> x >> y;
      const auto func = [&](const ll k) {
        return a + b * k + k * (k + 1) / 2 * x;
      };
      if (x > 0) {
        res = max ({res, func (1), func (y)});
      } else {
        int l = 0, r = y + 1;
        while (r - l > 2) {
          const ll mid1 = (l + r) / 2, mid2 = mid1 + 1;
          func (mid1) < func (mid2) ? l = mid1 : r = mid2;
        }
        res = max (res, func (l + 1));
      }
      a = func (y), b += x * y;
    }
    cout << res << "\n";
  }
  return 0;
}