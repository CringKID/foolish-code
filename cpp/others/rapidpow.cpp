#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;
using ll = long long;
const int kLen = 1 << 16;

ll x, y, mod, block, rp[kLen + 5][2];
void init () {
  block = sqrt (mod), rp[0][0] = rp[0][1] = 1;
  for (int i = 1; i <= block; i++) {
    rp[i][0] = rp[i - 1][0] * x % mod;
  }
  for (int i = 1; i <= block; i++) {
    rp[i][1] = rp[i - 1][1] * rp[block][0] % mod;
  }
}
ll rapidpow (ll base) {
  ll rec = mod;
  for (int i = 2; i * i <= mod; i++) {
    if (!(mod % i)) {
      rec = rec / i * (i - 1);
    }
    while (!(mod % i)) {
      mod /= i;
    }
  }
  if (mod > 1) {
    rec = rec / mod * (mod - 1);
  }
  base %= rec;
  return rp[base % block][0] * rp[base / block][1] % mod;
}
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> x >> y >> mod;
  init ();
  cout << rapidpow (y) << '\n';
  return 0;
}