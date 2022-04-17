#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;
const int kMaxN = 1e6 + 5, kMod = 1e9 + 7;

ll n, m, arr[kMaxN], ans[kMaxN];
bool check (ll x) {
  ll rec = 0;
  for (ll i = n; i > 0; i--) {
    rec = (rec + arr[i]) * x % kMod;
  }
  rec = (rec + arr[0]) % kMod;
  return !rec;
}
int main () {
  cin >> n >> m;
  for (ll i = 0; i <= n; i++) {   
    cin >> arr[i];
  }
  for (ll i = 1; i <= m; i++) {
    if (check (i)) {
      ans[++ans[0]] = i;
    }
  }
  for (ll i = 0; i <= ans[0]; i++) {
    cout << ans[i] << '\n';
  }
  return 0;
}