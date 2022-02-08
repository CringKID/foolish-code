#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
using ll = long long;
using Pii = pair <int, int>;
using Pll = pair <ll, ll>;
const int kMaxN = 1e3 + 5, kMod = 1e9 + 7, kInf = 1e9;

int n, m, t, arr[kMaxN], cnt[kMaxN];
vector <int> ve[kMaxN];
bool DFS (int now, int cur) {
  if (cnt[now] == cur) {
    return false;
  }
  cnt[now] = cur;
  for (int to : ve[now]) {
    if (!arr[to] || DFS (arr[to], cur)) {
      return arr[to] = now;
    }
  }
  return false;
}
//#define contest
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);
#ifdef contest
  freopen (, , stdin);
  freopen (, , stdout);
#endif

  cin >> n >> m >> t;
  for (int i = 1, from, to; i <= t; i++) {
    cin >> from >> to;
    ve[from].emplace_back (to);
  }
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    if (DFS (i, i)) {
      ans++;
    }
  }
  cout << ans << '\n';
  return 0;
}