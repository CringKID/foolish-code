#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <tuple>

using namespace std;
using Pii = pair <int, int>;
using Tiii = tuple <int, int, int>;
const int kMaxN = 2e5 + 5;
vector <Pii> ve[kMaxN];
int fa[kMaxN][20];
int maxv[kMaxN][20];
int depth[kMaxN];
void dfs (int x, int p = 0) {
  depth[x] = depth[p] + 1;
  fa[x][0] = p;
  for (Pii pp : ve[x]) {
    int y, w; tie (y, w) = pp;
    if (y == p) {
      continue;
    }
    maxv[y][0] = w;
    dfs (y, x);
  }
}
void init (int n) {
  dfs (1);
  for (int i = 1; i < 20; i++) {
    for (int j = 1; j <= n; j++) {
      int p = fa[j][i - 1];
      fa[j][i] = fa[p][i - 1];
      maxv[j][i] = max (maxv[j][i - 1], maxv[p][i - 1]);
    }
  }
}
int moveup (int x, int d) {
  for (int i = 0; d >> i; i++) {
    if (d >> i & 1) {
      x = fa[x][i];
    }
  }
  return x;
}
int getlca (int x, int y) {
  if (depth[x] < depth[y]) {
    swap (x, y);
  }
  x = moveup (x, depth[x] - depth[y]);
  if (x == y) {
    return x;
  }
  for (int i = 19; i >= 0; i--) {
    if (fa[x][i] != fa[y][i]) {
      x = fa[x][i], y = fa[y][i];
    }
  }
  return fa[x][0];
}
int getans (int x, int d) {
  int ans = 0;
  for (int i = 0; d >> i; i++) {
    if (d >> i & 1) {
      ans = max (ans, maxv[x][i]);
      x = fa[x][i];
    }
  }
  return ans;
}
int solve (int x, int y, int w) {
  int lca = getlca (x, y);
  return max (getans (x, depth[x] - depth[lca]), getans (y, depth[y] - depth[lca])) == w;
}
struct UFS {
  int p[kMaxN];
  void init (int n = kMaxN) {
    memset(p, -1, sizeof (int) * n);
  }
  int treesize (int x) {
    return -p[Find (x)];
  }
  int Find (int x) {
    int s = x;
    while (p[s] >= 0) {
      s = p[s];
    }
    while (x != s) {
      int t = p[x];
      p[x] = s;
      x = t;
    }
    return s;
  }
  void Union (int x, int y) {
    int px = Find (x), py = Find (y);
    if (p[px] > p[py]) {
      swap (px, py);
    }
    p[px] += p[py], p[py] = px;
  }
} uf;

int main() {
  int n, m; cin >> n >> m; uf.init();
  vector <Tiii> vp;
  while (m--) {
    int x, y, w; cin >> x >> y >> w;
    vp.emplace_back (w, x, y);
  }
  sort (vp.begin (), vp.end ());
  for (Tiii p : vp) {
    int x, y, w; tie (w, x, y) = p;
    if (uf.Find (x) == uf.Find (y)) {
      continue;
    }
    uf.Union (x, y);
    ve[x].emplace_back (y, w);
    ve[y].emplace_back (x, w);
  }
  init (n);
  int ans = 1 - n;
  for (Tiii p : vp) {
    int x, y, w; tie(w, x, y) = p;
    ans += solve (x, y, w);
  }
  cout << ans << '\n';
  return 0;
}