#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;
const ll kMaxN = 1 << 17, kMaxM = 289, kMod = 998244353;

ll n, m, dp1[kMaxN], dp2[kMaxN], arr1[kMaxM], arr2[kMaxM], bit[kMaxM], ans[25];
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n >> m, bit[0] = 1;
  for (int i = 1; i <= m; i++) {
    bit[i] = bit[i - 1] * 2 % kMod;
    cin >> arr1[i] >> arr2[i];
    arr1[i]--, arr2[i]--;
  }
  for (int i = 0; i < 1 << n; i++) {
    for (int j = 1; j <= m; j++) {
      if (((i >> arr1[j]) & 1) && ((i >> arr2[j]) & 1)) {
        dp2[i]++;
      }
    }
  }
  for (int i = 0; i < 1 << n; i++) {
    int x = 0;
    for (int j = 0; j < n; j++) {
      if (i >> j & 1) {
        x = j;
        break;
      }
    }
    dp1[i] = bit[dp2[i]];
    for (int j = (i - 1) & i; j; j = (j - 1) & i) {
      if (!(j >> x & 1)) {
        continue;
      }
      dp1[i] = (dp1[i] - dp1[j] * bit[dp2[i - j]] % kMod) % kMod;
    }
  }
  for (int i = 0; i < 1 << n; i++) {
    if (!(i & 1)) {
      continue;
    }
    ll cur = dp1[i] * bit[dp2[(1 << n) - 1 - i]] % kMod;
    for (int j = 0; j < n; j++) {
      if (!(i >> j & 1)) {
        continue;
      }
      ans[j] = (ans[j] + cur) % kMod;
    }
  }
  for (int i = 1; i < n; i++) {
    cout << (ans[i] % kMod + kMod) % kMod << '\n';
  }
  return 0;
}