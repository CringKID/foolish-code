#include <bits/stdc++.h>
using namespace std;
int n, m, op, a, b;
struct leftpiantree {
  int dis, val, lch, rch, f;
} lt[100005];
inline int find(int x) {
  if (lt[x].f == x) return x;
  return lt[x].f = find(lt[x].f);
}
inline int merge(int x, int y) {
  if (!x || !y) return x + y;
  if (lt[x].val > lt[y].val) swap(x, y);
  if (x > y && lt[x].val == lt[y].val) swap(x, y);
  int ls = lt[x].lch, rs = lt[x].rch;
  rs = merge(rs, y);
  if (lt[ls].dis < lt[rs].dis) swap(ls, rs);
  lt[ls].f = lt[rs].f = lt[x].f = x;
  lt[x].dis = lt[rs].dis + 1;
  lt[x].lch = ls, lt[x].rch = rs;
  return x;
}
int main() {
  scanf("%d %d", &n, &m);
  lt[0].dis = -1;
  for (int i = 1; i <= n; i++) {
    lt[i].f = i;
    scanf("%d", &lt[i].val);
  }
  while (m--) {
    int op, a, b;
    scanf("%d", &op);
    if (op == 1) {
      scanf("%d %d", &a, &b);
      if (!~lt[a].val) continue;
      if (!~lt[b].val) continue;
      int fa = find(a), fb = find(b);
      if (fa != fb) lt[fa].f = lt[fb].f = merge(fa, fb);
    } else {
      scanf("%d", &a);
      if (~lt[a].val) {
        int father = find(a);
        int ls = lt[father].lch;
        int rs = lt[father].rch;
        printf("%d\n", lt[father].val);
        lt[father].val = -1;
        lt[ls].f = ls, lt[rs].f = rs;
        lt[father].f = merge(ls, rs);
      } else
        printf("-1\n");
    }
  }
  return 0;
}