#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
using ll = long long;
const ll kMaxN = 16, kMaxM = 1e4 + 5, kInf = 1e18;

ll n, m, rec1[kMaxN][kMaxN], rec2[kMaxN][kMaxN], arr[kMaxN][kMaxM], dp[kMaxN][kMaxN][1 << kMaxN];
ll solve (ll x, ll y, ll z) {
  if (z + 1 == (1 << n)) {
    return rec2[x][y];
  }
  ll &cur = dp[x][y][z];
  if (~cur) {
    return cur;
  }
  cur = 0;
  for (int i = 0; i < n; i++) {
    if (z >> i & 1) {
      continue;
    }
    cur = max (cur, min (rec1[y][i], solve (x, i, z | (1 << i))));
  }
  return cur;
}
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  memset (dp, -1, sizeof (dp));
  cin >> n >> m;
  for (ll i = 0; i < n; i++) {
    for (ll j = 0; j < m; j++) {
      cin >> arr[i][j];
    }
  }
  for (ll i = 0; i < n; i++) {
    for (ll j = 0; j < n; j++) {
      ll ans = abs (arr[j][0] - arr[i][0]);
      rec2[i][j] = kInf;
      for (int k = 1; k < m; k++) {
        ans = min (ans, abs (arr[j][k] - arr[i][k]));
        rec2[i][j] = min (rec2[i][j], abs (arr[j][k] - arr[i][k - 1]));
      }
      rec1[i][j] = ans;
    }
  }
  ll ans = 0;
  for (int i = 0; i < n; i++) {
    ans = max (ans, solve (i, i, 1 << i));
  }
  cout << ans << '\n';
  return 0;
}