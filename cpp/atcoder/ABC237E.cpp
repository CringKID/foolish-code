#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;
using ll = long long;
using Pii = pair <int, int>;
using Pll = pair <ll, ll>;
const int kMaxN = 2e5 + 5, kMod = 1e9 + 7, kInf = 1e9;

struct Node {
  ll pos, dist;
  bool operator < (const Node &a) const { return dist > a.dist; }
}; priority_queue <Node> que;
vector <Pii> edge[kMaxN];
ll n, m, ans, h[kMaxN], d[kMaxN];
bool vis[kMaxN];
//#define contest
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);
#ifdef contest
  freopen (, , stdin);
  freopen (, , stdout);
#endif

  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> h[i], d[i] = 1e18;
  }
  for (int i = 1, from, to; i <= m; i++) {
    cin >> from >> to;
    edge[from].push_back ({to, max (h[to] - h[from], 0ll)});
    edge[to].push_back ({from, max (h[from] - h[to], 0ll)});
  }
  que.push ({1, 0}), d[1] = 0;
  while (!que.empty ()) {
    Node now = que.top (); que.pop ();
    if (vis[now.pos]) {
      continue;
    }
    vis[now.pos] = true;
    for (Pii i : edge[now.pos]) {
      if (d[i.first] > d[now.pos] + i.second) {
        d[i.first] = d[now.pos] + i.second;
        que.push ({i.first, d[i.first]});
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    ans = max (ans, h[1] - h[i] - d[i]);
  }
  cout << ans << '\n';
  return 0;
}