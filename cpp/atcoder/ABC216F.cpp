#include <bits/stdc++.h>

using namespace std;
using Pii = pair <int, int>;
const int kMaxN = 5e3 + 5, kMod = 998244353;

int dp[kMaxN], n;
pair <int, int> P[kMaxN];
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> P[i].first;
  }
  for (int i = 1; i <= n; i++) {
    cin >> P[i].second;
  }
  sort (P + 1, P + n + 1);
  fill (dp, dp + P[n].first + 1, 1);
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    if (P[i].first >= P[i].second) {
      (ans += dp[P[i].first - P[i].second]) %= kMod;
    }
    for (int j = P[n].first; j >= P[i].second; j--) {
      (dp[j] += dp[j - P[i].second]) %= kMod;
    }
  }
  cout << ans << '\n';
  return 0;
}
