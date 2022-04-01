#include <iostream>
#include <algorithm>
#include <deque>
#include <cstring>

using namespace std;
using ll = long long;
using Pll = pair <ll, ll>;
const int kMaxN = 5e3 + 5;

int n, m, x;
ll dp[kMaxN][kMaxN], ans = -1, arr[kMaxN];
deque <Pll> dq[kMaxN];
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n >> m >> x;
  for (int i = 1; i <= n; i++) {
    cin >> arr[i];
  }
  memset (dp, -1, sizeof (dp));
  dp[0][0] = 0;
  dq[0].emplace_back (0, 0);
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j <= i && j <= x; j++) {
      for ( ; !dq[j].empty () && dq[j].front ().second < i - m; dq[j].pop_front ()) {
      }
    }
    for (int j = 1; j <= i && j <= x; j++) {
      if (!dq[j - 1].empty () && ~dq[j - 1].front ().first) {
        dp[i][j] = dq[j - 1].front ().first + arr[i];
      }
    }
    for (int j = 0; j <= i && j <= x; j++) {
      for ( ; !dq[j].empty () && dp[i][j] >= dq[j].back ().first; dq[j].pop_back ()) {
      }
      if (~dp[i][j]) {
        dq[j].emplace_back (dp[i][j], i);
      }
    }
    if (n - i < m) {
      ans = max (ans, dp[i][x]);
    }
  }
  cout << ans << '\n';
  return 0;
}