#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;
const int kMaxN = 2e5 + 5;

int val[kMaxN], n, q, x;
struct SegTree {
struct Node {
  int l, r, val, tag;
} tree[kMaxN << 2];
void pushup (int x) {
  tree[x].val = tree[x << 1].val + tree[x << 1 | 1].val;
}
void pushdown (int x) {
  Node &rt = tree[x], &lx = tree[x << 1], &rx = tree[x << 1 | 1];
  if (~rt.tag) {
    lx.tag = rt.tag, lx.val = rt.tag * (lx.r - lx.l + 1);
    rx.tag = rt.tag, rx.val = rt.tag * (rx.r - rx.l + 1);
    rt.tag = -1;
  }
}
void build (int rt, int l, int r, int x) {
  tree[rt] = {l, r}, tree[rt].tag = -1;
  if (l == r) {
    return tree[rt].val = (val[l] >= x), void ();
  }
  int mid = l + r >> 1;
  build (rt << 1, l, mid, x), build (rt << 1 | 1, mid + 1, r, x), pushup (rt);
}
void update (int rt, int l, int r, int x) {
  if (l <= tree[rt].l && tree[rt].r <= r) {
    return tree[rt].tag = x, tree[rt].val = x * (tree[rt].r - tree[rt].l + 1), void ();
  }
  pushdown (rt);
  int mid = tree[rt].l + tree[rt].r >> 1;
  (l <= mid ? update (rt << 1, l, r, x) : void ());
  (r > mid ? update (rt << 1 | 1, l, r, x) : void ());
  pushup (rt);
}
int query (int x, int l, int r) {
  if (l <= tree[x].l && tree[x].r <= r) {
    return tree[x].val;
  }
  pushdown (x);
  int mid = tree[x].l + tree[x].r >> 1;
  return (l <= mid ? query (x << 1, l, r) : 0) + (r > mid ? query (x << 1 | 1, l, r) : 0);
}
} seg1, seg2;
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n >> q >> x;
  for_each (val + 1, val + n + 1, [] (int &x) { cin >> x; });
  seg1.build (1, 1, n, x), seg2.build (1, 1, n, x + 1);
  for (int opt, l, r; q--; ) {
    cin >> opt >> l >> r;
    int cur1 = seg1.query (1, l, r), cur2 = seg2.query (1, l, r), len = r - l + 1;
    if (opt == 1) {
      (cur1 && cur1 != len ? seg1.update (1, l, r - cur1, 0), seg1.update (1, r - cur1 + 1, r, 1) : void ());
      (cur2 && cur2 != len ? seg2.update (1, l, r - cur2, 0), seg2.update (1, r - cur2 + 1, r, 1) : void ());
    } else {
      (cur1 && cur1 != len ? seg1.update (1, l, l + cur1 - 1, 1), seg1.update (1, l + cur1, r, 0) : void ());
      (cur2 && cur2 != len ? seg2.update (1, l, l + cur2 - 1, 1), seg2.update (1, l + cur2, r, 0) : void ());
    }
  }
  for (int i = 1; i <= n; i++) {
    if (seg1.query (1, i, i) != seg2.query (1, i, i)) {
      cout << i << '\n';
    }
  }
  return 0;
}