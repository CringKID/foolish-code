#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
using ll = long long;
using Pii = pair <int, int>;
using Pll = pair <ll, ll>;
const int kMaxN = 1e4 + 5, kMod = 1e9 + 7, kInf = 1e9;

struct Node {
  int sum, coin;
} node[kMaxN];
int n, k, dp[kMaxN];
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  while (cin >> n >> k && n && k) {
    for (int i = 1; i <= n; i++) {
      cin >> node[i].sum;
    }
    for (int i = 1; i <= n; i++) {
      cin >> node[i].coin;
    }
    sort (node + 1, node + n + 1, [] (Node n1, Node n2) {
      return n1.coin > n2.coin;
    });
    memset (dp, 0, sizeof (dp));
    for (int i = 1; i <= n; i++) {
      for (int j = k; j > 0; j--) {
        dp[j] = max (dp[j], dp[j - 1] + node[i].sum - node[i].coin * (j - 1));
      }
    }
    int ans = 0;
    for (int i = 0; i <= k; i++) {
      ans = max (ans, dp[i]);
    }
    cout << ans << '\n';
  }
  return 0;
}