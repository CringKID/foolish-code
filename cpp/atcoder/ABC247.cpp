#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
using ll = long long;
using Pii = pair <int, int>;
using Pll = pair <ll, ll>;
const int kMaxN = 2e5 + 5, kMod = 1e9 + 7, kInf = 1e9;

int T, n, m, t;
bool vis[kMaxN];
vector <int> ve[kMaxN], ans[2];
void DFS (int x, bool cur) {
  vis[x] = 1, ans[cur].push_back (x);
  for (int i = 0; i < ve[x].size (); i++) {
    if (vis[ve[x][i]]) {
      continue;
    }
    DFS (ve[x][i], !cur);
  }
}
//#define contest
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);
#ifdef contest
  freopen (, , stdin);
  freopen (, , stdout);
#endif

  cin >> T;
  while (T--) {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
      ve[i].clear (), vis[i] = 0;
    }
    ans[0].clear (), ans[1].clear ();
    for (int i = 1, from, to; i <= m; i++) {
      cin >> from >> to;
      ve[from].push_back (to), ve[to].push_back (from);
    }
    DFS (1, 0);
    cout << min (ans[0].size (), ans[1].size ()) << '\n';
    if (ans[0].size () > ans[1].size ()) {
      swap (ans[0], ans[1]);
    }
    for (int i = 0; i < ans[0].size (); i++) {
      cout << ans[0][i] << ' ';
    }
    cout << '\n';
  }
  return 0;
}