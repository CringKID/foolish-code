#include <iostream>
#include <algorithm>

using namespace std;
const int kMaxN = 4e5 + 10, kInf = 1e9 + 10;

struct Edge {
  int to, next;
} edge[kMaxN];
struct Node {
  int sum, tag;
} tr[kMaxN];
int tot, head[kMaxN], fath[kMaxN], dep[kMaxN], dfn[kMaxN], top[kMaxN], siz[kMaxN], cnt, son[kMaxN], n, m, from[kMaxN], to[kMaxN];
void add (int x, int y) {
  edge[++tot] = {y, head[x]}, head[x] = tot;
  edge[++tot] = {x, head[y]}, head[y] = tot;
}
void dfs1 (int x, int fa) {
  fath[x] = fa, dep[x] = dep[fa] + 1, siz[x] = 1;
  for (int i = head[x], to; i; i = edge[i].next) {
    to = edge[i].to;
    if (to == fath[x]) {
      continue;
    }
    dfs1 (to, x), siz[x] += siz[to];
    siz[to] > siz[son[x]] ? son[x] = to : 0;
  }
}
void dfs2 (int x, int fa) {
  top[x] = fa, dfn[x] = ++cnt;
  son[x] ? dfs2 (son[x], fa) : void ();
  for (int i = head[x], to; i; i = edge[i].next) {
    to = edge[i].to;
    if (top[to]) {
      continue;
    }
    dfs2 (to, to);
  }
}
void pushup (int x) {
  tr[x].sum = min (tr[x << 1].sum, tr[x << 1 | 1].sum);
}
void pushdown (int x) {
  if (tr[x].tag != kInf) {
    tr[x << 1].tag = min (tr[x << 1].tag, tr[x].tag), tr[x << 1 | 1].tag = min (tr[x << 1 | 1].tag, tr[x].tag);
    tr[x << 1].sum = min (tr[x << 1].sum, tr[x].tag), tr[x << 1 | 1].sum = min (tr[x << 1 | 1].sum, tr[x].tag);
    tr[x].tag = kInf;
  }
}
void build (int x, int l, int r) {
  tr[x].tag = tr[x].sum = kInf;
  if (l == r) {
    return ;
  }
  int mid = (l + r) >> 1;
  build (x << 1, l, mid), build (x << 1 | 1, mid + 1, r);
}
int query(int x, int l, int r, int sum) {
  if (l == r) {
    return tr[x].sum;
  }
  pushdown (x);
  int mid = l + r >> 1;
  return (sum <= mid ? query (x << 1, l, mid, sum) : query (x << 1 | 1, mid + 1, r, sum));
}
void update (int rt, int l, int r, int x, int y, int z) {
  if (x <= l && y >= r) {
    return tr[rt].sum = min (tr[rt].sum, z), tr[rt].tag = min (tr[rt].tag, z), void ();
  }
  pushdown (rt);
  int mid = (l + r) >> 1;
  x <= mid ? update (rt << 1, l, mid, x, y, z) : void ();
  y > mid ? update (rt << 1 | 1, mid + 1, r, x, y, z) : void ();
  pushup (rt);
}
void update (int x, int y, int z) {
  for ( ; top[x] != top[y]; x = fath[top[x]]) {
    dep[top[x]] < dep[top[y]] ? swap (x, y) : void ();
    update (1, 1, n, dfn[top[x]], dfn[x], z);
  }
  dep[x] > dep[y] ? swap (x, y) : void ();
  update (1, 1, n, dfn[x] + 1, dfn[y], z);
}
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n >> m;
  for (int i = 1; i < n; i++) {
    cin >> from[i] >> to[i], add (from[i], to[i]);
  }
  dfs1 (1, 0), dfs2 (1, 1), build (1, 1, n);
  for (int i = 1, x, y, z; i <= m; i++) {
    cin >> x >> y >> z, update (x, y, z);
  }
  for (int i = 1, u, v, ans; i < n; ++i) {
    u = from[i], v = to[i];
    dep[u] < dep[v] ? swap (u, v) : void ();
    ans = query (1, 1, n, dfn[u]);
    cout << (ans == kInf ? -1 : ans) << '\n';
  }
  return 0;
}