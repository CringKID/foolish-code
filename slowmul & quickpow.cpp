#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;
const int kMaxN = 1e5 + 5;

ll slowmul (ll multi1, ll multi2, ll mod) {
  ll ans = 0;
  while (multi2) {
    if (multi2 & 1) {
      ans = (ans + multi1) % mod;
    }
    multi1 = (multi1 << 1) % mod;
    multi2 >>= 1;
  }
  return ans;
}
ll quickpow (ll base, ll index, ll mod) {
  ll ans = 0;
  while (index) {
    if (index & 1) {
      ans = ans * base % mod;
    }
    base = base * base % mod;
    index >>= 1;
  }
  return ans;
}
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  return 0;
}