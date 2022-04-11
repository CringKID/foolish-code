#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;
using ll = long long;
const int kMaxN = 2e6 + 5, kMod = 998244353;

int cnt;
ll n, arr[kMaxN], ans;
void prime () {
  for (ll i = 1; i <= sqrt (n); i++) {
    if (!(n % i)) {
      arr[++cnt] = i;
      if (n / i != i) {
        arr[++cnt] = n / i;
      }
    }
  }
}
ll solve (ll n) {
  ll cur = n;
  for (ll i = 2; i <= sqrt (n); i++) {
    if (!(n % i)) {
      cur = cur / i * (i - 1);
      for ( ; !(n % i); n /= i) {
      }
    }
  }
  return (n > 1 ? cur / n * (n - 1) : cur) % kMod;
}
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n, n--, prime ();
  for (int i = 1; i <= cnt; i++) {
    ans = (ans + (n / arr[i]) % kMod * solve (n / arr[i]) % kMod) % kMod;
  }
  cout << ans + 1 << '\n';
  return 0;
}