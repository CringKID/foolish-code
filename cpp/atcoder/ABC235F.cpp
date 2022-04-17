#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;
using Pii = pair <int, int>;
using Pll = pair <ll, ll>;
const int kMaxN = 1e5 + 5, kMaxM = 1 << 11, kMod = 998244353, kInf = 1e9;

int n, m, k, arr[kMaxN], tot;
ll dp1[kMaxN][kMaxM], dp2[kMaxN][kMaxM];
//#define contest
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);
#ifdef contest
  freopen (, , stdin);
  freopen (, , stdout);
#endif

  string str; cin >> str;
  int n = str.size ();
  for (int i = 0; i < n; i++) {
    arr[i] = str[i] - '0';
  }
  cin >> m;
  int rec = 0;
  for (int i = 0, x; i < m; i++) {
    cin >> x, rec |= 1 << x;
  }
  int pre = arr[0], prebit = 1 << arr[0];
  for (int i = 1; i < arr[0]; i++) {
    (dp1[0][1 << i] += 1) %= kMod;
    (dp2[0][1 << i] += i) %= kMod;
  }
  for (int i = 1; i < n; i++) {
    for (int j = 1; j < (1 << 10); j++) {
      for (int k = 0; k < 10; k++) {
        dp1[i][j | (1 << k)] = (dp1[i][j | (1 << k)] + dp1[i - 1][j] + kMod) % kMod;
        dp2[i][j | (1 << k)] = (dp2[i][j | (1 << k)] + dp2[i - 1][j] * 10 + dp1[i - 1][j] * k + kMod) % kMod;
      }
    }
    for (int k = 1; k <= 10; k++) {
      dp1[i][1 << k] = (dp1[i][1 << k] + 1 + kMod) % kMod;
      dp2[i][1 << k] = (dp2[i][1 << k] + k + kMod) % kMod;
    }
    for (int k = 0; k < arr[i]; k++) {
      dp1[i][prebit | (1 << k)] = (dp1[i][prebit | (1 << k)] + 1 + kMod) % kMod;
      dp2[i][prebit | (1 << k)] = (dp2[i][prebit | (1 << k)] + 1ll * pre * 10 + k + kMod) % kMod;
    }
    pre = (1ll * pre * 10 + arr[i] + kMod) % kMod;
    prebit = prebit | (1 << arr[i]);
  }
  ll reg = 0;
  for (int j = 0; j < (1 << 10); j++) {
    if ((j & rec) == rec) {
      reg = (reg + dp2[n - 1][j]) % kMod;
    }
  }
  if ((prebit & rec) == rec) {
    reg = (reg + pre) % kMod;
  }
  cout << reg << '\n';
  return 0;
}