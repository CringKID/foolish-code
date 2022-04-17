#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;
using Pii = pair <int, int>;
using Pll = pair <ll, ll>;
const int kMaxN = 5e5 + 5, kMod = 1e9 + 7, kInf = 1e9;

struct Edge {
  ll to, next, v1, v2;
} edge[kMaxN];
ll head[kMaxN], tot, dep[kMaxN], fath[kMaxN][25], cnt[kMaxN], n, k, ans;
void add_ (ll from, ll to, ll v1, ll v2) {
  edge[++tot] = {to, head[from], v1, v2}, head[from] = tot;
}
void add (ll from, ll to, ll v1, ll v2) {
  add_ (from, to, v1, v2), add_ (to, from, v1, v2);
}
void DFS1 (ll x, ll fa) {
  for (ll i = head[x]; i; i = edge[i].next) {
    ll to = edge[i].to;
    if (to == fa) {
      continue;
    }
    dep[to] = dep[x] + 1, fath[to][0] = x;
    DFS1 (to, x);
  }
}
void DFS2 (ll x, ll fa, ll cur) {
  for (ll i = head[x]; i; i = edge[i].next) {
    ll to = edge[i].to;
    if (to == fa) {
      continue;
    }
    DFS2 (to, x, i);
  }
  cnt[fa] += cnt[x], ans += min (cnt[x] * edge[cur].v1, edge[cur].v2);
}
ll lca (ll x, ll y) {
  ll s1, s2;
  if (dep[x] < dep[y]) {
    swap (x, y);
  }
  for (s1 = 0; (1 << s1) <= dep[x]; s1++) {
  }
  for (s2 = --s1; s2 >= 0; s2--) {
    if (dep[x] - (1 << s2) >= dep[y]) {
      x = fath[x][s2];
    }
  }
  if (x == y) {
    return x;
  }
  for (s2 = s1; s2 >= 0; s2--) {
    if (fath[x][s2] != fath[y][s2]) {
      x = fath[x][s2], y = fath[y][s2];
    }
  }
  return fath[x][0];
}

//#define contest
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);
#ifdef contest
  freopen (, , stdin);
  freopen (, , stdout);
#endif

  cin >> n;
  for (ll i = 1, from, to, v1, v2; i < n; i++) {
    cin >> from >> to >> v1 >> v2;
    add (from, to, v1, v2);
  }
  DFS1 (1, 0);
  for (ll i = 1; (1 << i) <= n; i++) {
    for (ll j = 1; j <= n; j++) {
      fath[j][i] = fath[fath[j][i - 1]][i - 1];
    }
  }
  for (int i = 2; i <= n; i++) {
    cnt[lca (i - 1, i)] -= 2;
    cnt[i - 1]++, cnt[i]++;
  }
  DFS2 (1, 0, 0);
  cout << ans << '\n';
  return 0;
}