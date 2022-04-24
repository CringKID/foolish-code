#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;
using Pii = pair <int, int>;
using Pll = pair <ll, ll>;
const int kMaxN = 2e5 + 5, kMod = 1e9 + 7, kInf = 1e9;

struct Edge {
  ll to, next, val;
} edge[kMaxN];
ll n, m, cnt, head[kMaxN], vis[kMaxN], cur[75], dist[kMaxN], ans;
void add (ll from, ll to, ll val) {
  edge[++cnt] = {to, head[from], val}, head[from] = cnt;
}
void solve (ll x) {
  for (int j = 62; j >= 0; j--) {
    if ((x >> j) & 1) {
      if (!cur[j]) {
        cur[j] = x;
        break;
      }
      x ^= cur[j];
    }
  }
}
void DFS (int x, ll dis) {
  vis[x] = 1, dist[x] = dis;
  for (int i = head[x]; i; i = edge[i].next) {
    ll to = edge[i].to, val = edge[i].val;
    if (!vis[to]) {
      DFS (to, dis ^ val);
    } else {
      solve (dist[to] ^ val ^ dis);
    }
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

  cin >> n >> m;
  for (ll i = 1, from, to, val; i <= m; i++) {
    cin >> from >> to >> val;
    add (from, to, val), add (to, from, val);
  }
  DFS (1, 0), ans = dist[n];
  for (int i = 62; i >= 0; i--) {
    if ((cur[i] ^ ans) > ans) {
      ans = cur[i] ^ ans;
    }
  }
  cout << ans << '\n';
  return 0;
}