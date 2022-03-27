#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
const int kMaxN = 4e5 + 5, kInf = 1e9;

int n, q, mod, cnt, root;
struct Segtree {
  int sum, max;
} tree[kMaxN];
struct Edge {
  int to, next;
} edge[kMaxN];
int tot, head[kMaxN], arr[kMaxN], dep[kMaxN], top[kMaxN], fath[kMaxN], siz[kMaxN], son[kMaxN], idx[kMaxN], dark[kMaxN];
void add (int from, int to) {
  edge[++tot] = {to, head[from]};
  head[from] = tot;
}
void pushup (int x) {
  tree[x] = {tree[x << 1].sum + tree[x << 1 | 1].sum, max (tree[x << 1].max, tree[x << 1 | 1].max)};
}
void build (int x, int l, int r) {
  if (l == r) {
    tree[x] = {arr[l], arr[l]};
    return ;
  }
  int mid = l + r >> 1;
  build (x << 1, l, mid), build (x << 1 | 1, mid + 1, r);
  pushup (x);
}
void update (int x, int l, int r, int k, int val) {
  if (l > k || r < k) {
    return ;
  } else if (l == r && l == k) {
    tree[x].max = tree[x].sum = val;
    return ;
  }
  int mid = l + r >> 1;
  if (k <= mid) {
    update (x << 1, l, mid, k, val);
  } else {
    update (x << 1 | 1, mid + 1, r, k, val);
  }
  pushup (x);
}
int querysum (int x, int l, int r, int L, int R) {
  if (R < l || r < L) {
    return 0;
  } else if (L <= l && r <= R) {
    return tree[x].sum;
  }
  int mid = l + r >> 1;
  return querysum (x << 1, l, mid, L, R) + querysum (x << 1 | 1, mid + 1, r, L, R);
}
int querymax (int x, int l, int r, int L, int R) {
  if (R < l || r < L) {
    return -kInf;
  } else if (L <= l && r <= R) {
    return tree[x].max;
  }
  int mid = l + r >> 1;
  return max (querymax (x << 1, l, mid, L, R), querymax (x << 1 | 1, mid + 1, r, L, R));
}
void DFS1 (int x, int fa, int depth) {
  dep[x] = depth, fath[x] = fa, siz[x] = 1;
  int sonsiz = 0;
  for (int i = head[x]; ~i; i = edge[i].next) {
    int to = edge[i].to;
    if (to == fath[x]) {
      continue;
    }
    DFS1 (to, x, depth + 1);
    siz[x] += siz[to];
    if (siz[to] > sonsiz) {
      sonsiz = siz[to];
      son[x] = to;
    }
  }
}
void DFS2 (int x, int tp) {
  idx[x] = ++cnt, arr[cnt] = dark[x], top[x] = tp;
  if (!son[x]) {
    return ;
  }
  DFS2 (son[x], tp);
  for (int i = head[x]; ~i; i = edge[i].next) {
    int to = edge[i].to;
    if (to == fath[x] || to == son[x]) {
      continue;
    }
    DFS2 (to, to);
  }
}
void swap (int &x, int &y) {
  x ^= y ^= x ^= y;
}
int Querysum (int x, int y) {
  int ans = 0;
  for ( ; top[x] != top[y]; x = fath[top[x]]) {
    if (dep[top[x]] < dep[top[y]]) {
      swap (x, y);
    }
    ans += querysum (1, 1, n, idx[top[x]], idx[x]);
  }
  if (dep[x] > dep[y]) {
    swap (x, y);
  }
  ans += querysum (1, 1, n, idx[x], idx[y]);
  return ans;
}
int Querymax (int x, int y) {
  int ans = -kInf;
  for ( ; top[x] != top[y]; x = fath[top[x]]) {
    if (dep[top[x]] < dep[top[y]]) {
      swap (x, y);
    }
    ans = max (ans, querymax (1, 1, n, idx[top[x]], idx[x]));
  }
  if (dep[x] > dep[y]) {
    swap (x, y);
  }
  ans = max (ans, querymax (1, 1, n, idx[x], idx[y]));
  return ans;
}
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n;
  memset (head, -1, sizeof (head));
  for (int i = 1, from, to; i < n; i++) {
    cin >> from >> to;
    add (from, to), add (to, from);
  }
  for (int i = 1; i <= n; i++) {
    cin >> dark[i];
  }
  for (int i = 1; i <= n << 2; i++) {
    tree[i].max = -kInf;
  }
  root = 1, DFS1 (root, 0, 1), DFS2 (root, root), build (1, 1, n);
  cin >> q;
  while (q--) {
    int x, y; char opt[11];
    cin >> opt >> x >> y;
    if (opt[0] == 'C') {
      update (1, 1, n, idx[x], y);
    } else if (opt[1] == 'S') {
      cout << Querysum (x, y) << '\n';
    } else {
      cout << Querymax (x, y) << '\n';
    }
  }
  return 0;
}