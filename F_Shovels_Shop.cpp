#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
using ll = long long;
const int kMaxN = 1e6 + 5;

ll dp[kMaxN], sum[kMaxN];
int n, m, k, cur[kMaxN], arr[kMaxN];
ll DFS (int x) {
  if (!x) {
    return 0;
  }
  if (~dp[x]) {
    return dp[x];
  }
  ll ans = 1e18;
  for (int i = x; i > 0; i--) {
    int to = cur[x - i + 1], l = i - 1, r = i + to - 1;
    ll now = DFS (i - 1), rec = now + sum[x] - sum[i - 1] - sum[r] + sum[l];
    ans = min (ans, rec);
  }
  dp[x] = ans;
  return dp[x];
}
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n >> m >> k;
  for (int i = 1; i <= n; i++) {
    cin >> arr[i];
  }
  sort (arr + 1, arr + n + 1);
  for (int i = 1; i <= min (n, 2000); i++) {
    sum[i] = sum[i - 1] + arr[i];
  }
  memset (dp, -1, sizeof (dp));
  for (int i = 1, x, y; i <= m; i++) {
    cin >> x >> y;
    cur[x] = max (cur[x], y);
  }
  cout << DFS (k) << '\n';
  return 0;
}