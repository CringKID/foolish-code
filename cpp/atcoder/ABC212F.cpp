#include <iostream>
#include <algorithm>
#include <set>

using namespace std;
const int kMaxN = 1e5 + 5, kSize = 20;

set <pair <int, int> > Set[kMaxN];
int n, m, q, x, y, z, from[kMaxN], to[kMaxN], s[kMaxN], t[kMaxN], dp[kMaxN][kSize];
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n >> m >> q;
  for (int i = 1; i <= m; i++) {
    cin >> from[i] >> to[i] >> s[i] >> t[i];
    Set[from[i]].insert (make_pair (s[i], i));
  }
  for (int i = 1; i <= m; i++) {
    set <pair <int, int> > :: iterator it;
    it = Set[to[i]].lower_bound (make_pair (t[i], 0));
    if (it != Set[to[i]].end ()) {
      dp[i][0] = it -> second;
    }
  }
  for (int i = 1; i <= kSize - 1; i++) {
    for (int j = 1; j <= m; j++) {
      dp[j][i] = dp[dp[j][i - 1]][i - 1];
    }
  }
  while (q--) {
    cin >> x >> y >> z;
    set <pair <int, int> > :: iterator it;
    it = Set[y].lower_bound (make_pair (x, 0));
    if (it == Set[y].end () || z <= s[it -> second]) {
      cout << y << '\n';
    } else {
      int now = it -> second;
      for (int i = kSize - 1; i >= 0; i--) {
        if (dp[now][i] && s[dp[now][i]] < z) {
          now = dp[now][i];
        }
      }
      if (t[now] < z) {
        cout << to[now] << '\n';
      } else {
        cout << from[now] << ' ' << to[now] << '\n';
      }
    }
  }
  return 0;
}