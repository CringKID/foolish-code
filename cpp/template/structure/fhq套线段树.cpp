#include <bits/stdc++.h>
const int maxn = 5e4 + 5, maxm = 1e6 + 5, inf = INT_MAX;
inline int read() {
  register int X = 0;
  register bool flag = 1;
  register char ch = getchar();
  while ((ch < '0' || ch > '9') && ch != '-') ch = getchar();
  if (ch == '-') flag = 0, ch = getchar();
  while (ch >= '0' && ch <= '9') {
    X = (X << 1) + (X << 3) + (ch ^ 48);
    ch = getchar();
  }
  return flag ? X : ~(X - 1);
}
int a[maxn], n, m, cnt;
struct sgtnode {
  int l, r, rt;
} tree[maxn << 2];
struct fhqnode {
  int son[2], key, val, size;
} t[maxm << 1];
inline int newnode(int val) {
  register int k = ++cnt;
  t[k].key = rand();
  t[k].val = val, t[k].size = 1;
  t[k].son[0] = t[k].son[1] = 0;
  return k;
}
namespace fhq_Treap {
inline void update(int rt) {
  t[rt].size = t[t[rt].son[0]].size + t[t[rt].son[1]].size + 1;
}
int merge(int l, int r) {
  if (!l || !r) return l + r;
  if (t[l].key > t[r].key) {
    t[l].son[1] = merge(t[l].son[1], r);
    update(l);
    return l;
  } else {
    t[r].son[0] = merge(l, t[r].son[0]);
    update(r);
    return r;
  }
}
void split(int rt, int val, int &l, int &r) {
  if (!rt) {
    l = r = 0;
    return;
  }
  if (val >= t[rt].val) {
    l = rt;
    split(t[rt].son[1], val, t[rt].son[1], r);
  } else {
    r = rt;
    split(t[rt].son[0], val, l, t[rt].son[0]);
  }
  update(rt);
}
inline void insert(int &rt, int val) {
  register int l = 0, r = 0;
  split(rt, val, l, r);
  rt = merge(merge(l, newnode(val)), r);
}
inline void delete_(int &rt, int val) {
  register int l = 0, r = 0, tmp = 0;
  split(rt, val, l, r), split(l, val - 1, l, tmp);
  tmp = merge(t[tmp].son[0], t[tmp].son[1]);
  rt = merge(l, merge(tmp, r));
}
inline int place(int &rt, int val) {
  register int l = 0, r = 0;
  split(rt, val - 1, l, r);
  register int ans = t[l].size;
  rt = merge(l, r);
  return ans;
}
inline int Find(int &rt, int val, int opt) {
  register int l = 0, r = 0;
  split(rt, val - opt, l, r);
  register int tmp = opt ? l : r;
  if (!tmp) return opt ? -inf : inf;
  while (t[tmp].son[opt]) tmp = t[tmp].son[opt];
  register int ans = t[tmp].val;
  rt = merge(l, r);
  return ans;
}

}  // namespace fhq_Treap
namespace Segment_Tree {
void build(int rt, int l, int r) {
  tree[rt].l = l, tree[rt].r = r;
  if (l == r) {
    tree[rt].rt = newnode(a[l]);
    return;
  }
  for (register int i = l; i <= r; i++) fhq_Treap::insert(tree[rt].rt, a[i]);
  register int mid = (l + r) >> 1;
  build(rt << 1, l, mid), build(rt << 1 | 1, mid + 1, r);
}
int rank(int rt, int l, int r, int val) {
  if (tree[rt].l >= l && tree[rt].r <= r) return fhq_Treap::place(tree[rt].rt, val);
  register int ans = 0, mid = (tree[rt].l + tree[rt].r) >> 1;
  if (l <= mid) ans += rank(rt << 1, l, r, val);
  if (r > mid) ans += rank(rt << 1 | 1, l, r, val);
  return ans;
}
inline int kth(int l, int r, int k) {
  register int lft = 0, rght = 1e8 + 1, ans = 0;
  while (lft < rght) {
    register int mid = (lft + rght) >> 1;
    if (rank(1, l, r, mid) < k)
      ans = mid, lft = mid + 1;
    else
      rght = mid;
  }
  return ans;
}
void change(int rt, int tmp, int val) {
  fhq_Treap::delete_(tree[rt].rt, a[tmp]);
  fhq_Treap::insert(tree[rt].rt, val);
  if (tree[rt].l == tree[rt].r) return;
  register int mid = (tree[rt].l + tree[rt].r) >> 1;
  if (tmp <= mid) change(rt << 1, tmp, val);
  if (tmp > mid) change(rt << 1 | 1, tmp, val);
}
int query(int rt, int l, int r, int val, int opt) {
  if (tree[rt].l >= l && tree[rt].r <= r) return fhq_Treap::Find(tree[rt].rt, val, opt);
  register int ans = opt ? -inf : inf;
  register int mid = (tree[rt].l + tree[rt].r) >> 1;
  if (l <= mid) ans = opt ? std::max(ans, query(rt << 1, l, r, val, opt)) : std::min(ans, query(rt << 1, l, r, val, opt));
  if (r > mid) ans = opt ? std::max(ans, query(rt << 1 | 1, l, r, val, opt)) : std::min(ans, query(rt << 1 | 1, l, r, val, opt));
  return ans;
}
}  // namespace Segment_Tree
int main() {
  srand(time(0));
  n = read(), m = read();
  for (register int i = 1; i <= n; i++) a[i] = read();
  Segment_Tree::build(1, 1, n);
  for (int i = 1; i <= m; i++) {
    register int opt = read();
    if (opt == 1) {
      register int l = read(), r = read(), k = read();
      printf("%d\n", Segment_Tree::rank(1, l, r, k) + 1);
    } else if (opt == 2) {
      register int l = read(), r = read(), k = read();
      printf("%d\n", Segment_Tree::kth(l, r, k));
    } else if (opt == 3) {
      register int place = read(), sum = read();
      Segment_Tree::change(1, place, sum);
      a[place] = sum;
    } else if (opt == 4) {
      register int l = read(), r = read(), k = read();
      printf("%d\n", Segment_Tree::query(1, l, r, k, 1));
    } else {
      register int l = read(), r = read(), k = read();
      printf("%d\n", Segment_Tree::query(1, l, r, k, 0));
    }
  }
  return 0;
}