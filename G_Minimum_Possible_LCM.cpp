#include <iostream>
#include <algorithm>
#include <climits>

using namespace std;
using ll = long long;
const ll kMaxN = 1e7 + 5, kInf = LLONG_MAX;

int n, pos[kMaxN], x, y;
ll arr[kMaxN], ans, mmin = kInf;
ll gcd (ll a, ll b) {
  return (b == 0) ? a : gcd (b, a % b);
}
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n;
  for (int i = 1, val; i <= n; i++) {
    cin >> val, arr[val]++;
    if (arr[val] > 1 && val < mmin) {
      mmin = val;
      x = pos[val];
      y = i;
    }
    pos[val] = i;
  }
  for (int i = 1; i < kMaxN; i++) {
    ll val = 0;
    for (int j = i; j < kMaxN; j += i) {
      if (!arr[j]) {
        continue;
      }
      if (!val) {
        val = j;
      } else {
        ll g = gcd (val / i, j / i);
        if (g == 1) {
          ans = 1ll * j / i * val;
          if (ans < mmin) {
            mmin = ans;
            x = pos[val];
            y = pos[j];
          }
        }
        break;
      }
    }
  }
  if (x > y) {
    swap (x, y);
  }
  cout << x << " " << y << '\n';
  return 0;
}