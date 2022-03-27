#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;
using ll = long long;
const ll kMaxN = 1e4 + 5, kInf = 1e9;

ll n, m, st0, td0, df[kMaxN], ans[2], head[kMaxN], tot;
struct Edge {
  ll y, next, f, v;
} edge[kMaxN << 4];

void Ins(ll x, ll y, ll f, ll v) {
  edge[++tot].y = y;
  edge[tot].f = f;
  edge[tot].v = v;
  edge[tot].next = head[x];
  head[x] = tot;
}
void Ins_flow(ll x, ll y, ll f, ll v) {
  Ins (x, y, f, v);
  Ins (y, x, 0, -v);
}
ll st, td, cn;
void Get_graph () {
  st = n + 1;
  td = cn = n + 2;
  for (ll i = 1; i <= cn - 2; ++i) {
    if (!df[i]) continue;
    df[i] > 0 ? Ins_flow (st, i, df[i], 0) : Ins_flow (i, td, -df[i], 0);
  }
  Ins_flow (td0, st0, kInf, 0);
}
ll flow, value, dis[kMaxN], vis[kMaxN], predge[kMaxN], f[kMaxN];
queue <ll> que;
bool spfa (ll st, ll td) {
  for (ll i = 1; i <= cn; i++) {
    dis[i] = kInf, vis[i] = 0;
  }
  dis[st] = 0, vis[st] = 1, f[st] = kInf, que.push (st);
  for (; !que.empty ();) {
    ll t = que.front (); que.pop(), vis[t] = 0;
    for (ll i = head[t]; i; i = edge[i].next) {
      if (edge[i].f && dis[t] + edge[i].v < dis[edge[i].y]) {
        dis[edge[i].y] = dis[t] + edge[i].v, predge[edge[i].y] = i;
        f[edge[i].y] = min (f[t], edge[i].f);
        if (!vis[edge[i].y]) {
          vis[edge[i].y] = 1, que.push (edge[i].y);
        }
      }
    }
  }
  return dis[td] ^ kInf;
}
void solve (ll st, ll td) {
  flow = 0, value = 0;
  for (; spfa(st, td); flow += f[td], value += f[td] * dis[td]) {
    for (ll k = td; k ^ st; k = edge[predge[k] ^ 1].y) {
      edge[predge[k]].f -= f[td], edge[predge[k] ^ 1].f += f[td];
    }
  }
}
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n >> m >> st0 >> td0, tot = 1;
  for (ll i = 1, x, y, f, v; i <= m; i++) {
    cin >> x >> y >> f >> v;
    if (v >= 0) {
      Ins_flow (x, y, f, v);
    } else {
      df[x] -= f;
      df[y] += f;
      ans[1] += f * v;
      Ins_flow (y, x, f, -v);
    }
  }
  Get_graph ();
  solve (st, td);
  ans[1] += value;
  solve (st0, td0);
  ans[0] = flow, ans[1] += value;
  cout << ans[0] << ' ' << ans[1] << '\n';
  return 0;
}