#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;
using ll = long long;
using Pii = pair <int, int>;
using Pll = pair <ll, ll>;
const ll kMaxN = 1e6 + 5, kMod = 1e9 + 7, kInf = 1e9;

ll n, m, s, t = 10000, tot = 1, head[kMaxN], dist[kMaxN];
struct Edge {
  ll to, next, dist;
} edge[kMaxN];
void add (ll from, ll to, ll dis) {
  edge[++tot] = {to, head[from], dis}, head[from] = tot;
}
bool BFS () {
  queue <ll> que;
  que.push (s), dist[s] = 1;
  while (!que.empty ()) {
    ll x = que.front (); que.pop ();
    for (ll i = head[x]; i; i = edge[i].next) {
      ll to = edge[i].to;
      if (edge[i].dist && !dist[to]) {
        dist[to] = dist[x] + 1;
        if (to == t) {
          return true;
        }
        que.push (to);
      }
    }
  }
  return false;
}
ll DFS (ll x, ll flow) {
  if (x == t) {
    return flow;
  }
  ll ans = 0;
  for (ll i = head[x]; i && flow; i = edge[i].next) {
    ll to = edge[i].to, rec = 0;
    if (!edge[i].dist || dist[to] != dist[x] + 1) {
      continue;
    }
    rec = DFS (to, min (flow, edge[i].dist));
    if (!rec) {
      dist[to] = 2e14;
    }
    edge[i].dist -= rec, edge[i ^ 1].dist += rec;
    ans += rec, flow -= rec;
  }
  return ans;
}
//#define contest
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);
#ifdef contest
  freopen (, , stdin);
  freopen (, , stdout);
#endif

  cin >> n >> m;
  for (ll i = 1, x; i <= n; i++) {
    cin >> x;
    if (x == 1) {
      add (s, i, 1), add (i, s, 0);
    } else {
      add (i, t, 1), add (t, i, 0);
    }
  }
  for (ll i = 1, x, y; i <= m; i++) {
    cin >> x >> y;
    add (x, y, 1), add (y, x, 1);
  }
  ll ans = 0, rec = 0;
  while (BFS ()) {
    ans += DFS (s, 2e14);
    memset (dist, 0, sizeof (dist));
  }
  cout << ans << '\n';
  return 0;
}