#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
const int kMaxN = 1e5 + 5;

vector <int> edge[kMaxN];
int cnt = 0, n, q, rec, dep[kMaxN], son[kMaxN], size[kMaxN], fath[kMaxN], dfn[kMaxN], top[kMaxN];
char opt[11];
struct Node {
  int val, tag, ls, rs;
} tree[kMaxN << 2];
void pushup (int x) {
  tree[x].val = tree[x << 1].val + tree[x << 1 | 1].val;
}
void pushdown (int x) {
  if (tree[x].tag + 1) {
    tree[x << 1].tag = tree[x << 1 | 1].tag = tree[x].tag;
    tree[x << 1].val = (tree[x << 1].rs - tree[x << 1].ls + 1) * tree[x].tag;
    tree[x << 1 | 1].val = (tree[x << 1 | 1].rs - tree[x << 1 | 1].ls + 1) * tree[x].tag;
    tree[x].tag = -1;
  }
}
void build (int x, int l, int r) {
  tree[x] = {0, -1, l, r};
  if (l == r) {
    return ;
  }
  int mid = tree[x].ls + tree[x].rs >> 1;
  build (x << 1, l, mid), build (x << 1 | 1, mid + 1, r);
}
void update (int x, int l, int r, int val) {
  if (tree[x].ls >= l && tree[x].rs <= r) {
    tree[x].val = (tree[x].rs - tree[x].ls + 1) * val;
    tree[x].tag = val;
    return ;
  }
  pushdown (x);
  int mid = tree[x].ls + tree[x].rs >> 1;
  if (l <= mid) {
    update (x << 1, l, r, val);
  } 
  if (r > mid) {
    update (x << 1 | 1, l, r, val);
  }
  pushup (x);
}
void add (int x, int val) {
  if (val) {
    while (top[x] != top[1]) {
      update (1, dfn[top[x]], dfn[x], val);
      x = fath[top[x]];
    }
    update (1, dfn[1], dfn[x], val);
  } else {
    update (1, dfn[x], dfn[x] + size[x] - 1, val);
  }
}

void DFS1 (int x, int fa) {
  dep[x] = dep[fa] + 1, fath[x] = fa, size[x] = 1;
  for (int i = 0; i < edge[x].size (); i++) {
    int to = edge[x][i];
    if (to == fa) {
      continue;
    }
    DFS1 (to, x);
    size[x] += size[to];
    if (size[to] > size[son[x]]) {
      son[x] = to;
    }
  }
}
void DFS2 (int x, int y) {
  dfn[x] = ++cnt, top[x] = y;
  if (!son[x]) {
    return ;
  }
  DFS2 (son[x], y);
  for (int i = 0; i < edge[x].size (); i++) {
    int to = edge[x][i];
    if (to == fath[x] || to == son[x]) {
      continue;
    }
    DFS2 (to, to);
  }
}
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n;
  for (int i = 2, x; i <= n; i++) {
    cin >> x, x++;
    edge[x].push_back (i);
    edge[i].push_back (x);
  }
  DFS1 (1, 0), DFS2 (1, 1), build (1, 1, cnt);
  cin >> q;
  for (int i = 1, x; i <= q; i++) {
    cin >> opt >> x;
    x++, rec = tree[1].val;
    if (opt[0] == 'i') {
      add (x, 1);
      cout << abs (rec - tree[1].val) << '\n';
    } else if (opt[0] == 'u') {
      add (x, 0);
      cout << abs (rec - tree[1].val) << '\n';
    }
  }
  return 0;
}