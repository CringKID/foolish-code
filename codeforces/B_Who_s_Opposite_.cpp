#include <iostream>
#include <algorithm>

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
    int a, b, c, n;
    cin >> a >> b >> c;
    n = 2 * abs (a - b);
    if (a > n || b > n || c > n) {
      cout << -1 << '\n';
      continue;
    }
    cout << (n / 2 + c - 1) % n + 1 << '\n';
  }
  return 0;
}