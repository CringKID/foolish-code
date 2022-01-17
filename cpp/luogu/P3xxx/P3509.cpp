#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;
using ll = long long;
using Pii = pair <int, int>;
using Pll = pair <ll, ll>;
const int kMaxN = 1e5 + 5, kMod = 1e9 + 7, kInf = 1e9;

ll n, k, m, arr[kMaxN], tmp[kMaxN];
int dp[kMaxN][2], cur[kMaxN];
//#define contest
int main() {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);
#ifdef contest
  freopen (, , stdin);
  freopen (, , stdout);
#endif

  cin >> n >> k >> m;
  for (int i = 1; i <= n; i++) {
    cin >> arr[i];
  }
  ll l = 1, r = k + 1, mmax = log2 (m) + 1;
  for (int i = 1; i <= n; i++) {
    while (r < n && arr[r + 1] - arr[i] < arr[i] - arr[l]) {
      l++, r++;
    }
    dp[i][0] = (arr[r] - arr[i] > arr[i] - arr[l] ? r : l);
  }
  if (m & 1) {
    for (int i = 1; i <= n; i++) {
      cur[i] = dp[i][0];
    }
  } else {
    for (int i = 1; i <= n; i++) {
      cur[i] = i;
    }
  }
  r = 1;
  tmp[0] = 1;
  for (int i = 1; i <= mmax; i++) {
    tmp[i] = tmp[i - 1] << 1;
  }
  for (int j = 1; j <= mmax; j++) {
    for (int i = 1; i <= n; i++) {
      dp[i][r] = dp[dp[i][r ^ 1]][r ^ 1];
    }
    if (m & tmp[j]) {
      for (int i = 1; i <= n; i++) {
        cur[i] = dp[cur[i]][r];
      }
    }
    r ^= 1;
  }
  for (int i = 1; i <= n; i++) {
    cout << cur[i] << ' ';
  }
  return 0;
}