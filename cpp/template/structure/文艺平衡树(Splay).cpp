#include <bits/stdc++.h>
using namespace std;
const int maxn = 100005;
int n, m, op, root, nodecnt;
struct node {
  int f, c, v, s, rev, son[2];
} tree[maxn];
inline int check(int x) {
  return tree[tree[x].f].son[1] == x;
}
inline void pushup(int x) {
  tree[x].s = tree[tree[x].son[0]].s + tree[tree[x].son[1]].s + tree[x].c;
}
inline void pushdown(int x) {
  if (tree[x].rev) {
    swap(tree[x].son[0], tree[x].son[1]);
    tree[x].rev = 0;
    tree[tree[x].son[0]].rev ^= 1;
    tree[tree[x].son[1]].rev ^= 1;
  }
  return;
}
inline void rotate(int x) {
  int y = tree[x].f, z = tree[y].f, k = check(x), v = tree[x].son[k ^ 1];
  tree[y].son[k] = v;
  tree[v].f = y;
  tree[z].son[check(y)] = x;
  tree[x].f = z;
  tree[x].son[k ^ 1] = y;
  tree[y].f = x;
  pushup(y);
  pushup(x);
}
inline void Splay(int x, int goal) {
  while (tree[x].f != goal) {
    if ((tree[tree[x].f].f) != goal) {
      if (check(x) == check(tree[x].f))
        rotate(tree[x].f);
      else
        rotate(x);
    }
    rotate(x);
  }
  if (!goal) root = x;
}
inline void find(int x) {
  if (!root) return;
  int pos = root;
  while (tree[pos].son[x > tree[pos].v] && x != tree[pos].v) {
    pos = tree[pos].son[x > tree[pos].v];
  }
  Splay(pos, 0);
  return;
}
inline void insert(int x) {
  int pos = root, fa = 0;
  while (pos && tree[pos].v != x) {
    fa = pos;
    pos = tree[pos].son[x > tree[pos].v];
  }
  pos = ++nodecnt;
  if (fa) tree[fa].son[x > tree[fa].v] = pos;
  tree[pos].son[1] = tree[pos].son[0] = 0;
  tree[pos].v = x;
  tree[pos].f = fa;
  tree[pos].s = tree[pos].c = 1;
  Splay(pos, 0);
  return;
}
inline int kth(int x) {
  int pos = root;
  while (1) {
    pushdown(pos);
    if (x <= tree[tree[pos].son[0]].s)
      pos = tree[pos].son[0];
    else if (x > tree[tree[pos].son[0]].s + tree[pos].c) {
      x -= tree[tree[pos].son[0]].s + 1;
      pos = tree[pos].son[1];
    } else
      return pos;
  }
}
inline void reverse(int l, int r) {
  l = kth(l), r = kth(r + 2);
  Splay(l, 0);
  Splay(r, l);
  tree[tree[tree[root].son[1]].son[0]].rev ^= 1;
  return;
}
inline void output(int x) {
  pushdown(x);
  if (tree[x].son[0]) output(tree[x].son[0]);
  if (tree[x].v > 1 && tree[x].v < n + 2) printf("%d ", tree[x].v - 1);
  if (tree[x].son[1]) output(tree[x].son[1]);
}
int main() {
  scanf("%d %d", &n, &m);
  int x, y;
  for (int i = 1; i <= n + 2; i++) insert(i);
  while (m--) {
    scanf("%d %d", &x, &y);
    reverse(x, y);
  }
  pushdown(root);
  output(root);
  printf("\n");
  return 0;
}