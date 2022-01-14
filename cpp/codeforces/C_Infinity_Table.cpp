#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;
using ll = long long;
using Pii = pair <int, int>;
using Pll = pair <ll, ll>;
const int kMaxN = 1e5 + 5, kMod = 1e9 + 7, kInf = 1e9;

int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  int T;
  cin >> T;
  while (T--) {
    int k;
    cin >> k;
    int cur = ceil (sqrt (k)), tmp = k - (cur - 1) * (cur - 1);
    if (tmp <= cur) {
      cout << tmp << ' ' << cur << '\n';
    } else {
      cout << cur << ' ' << cur - (tmp - cur) << '\n';
    }
  }
  return 0;
}