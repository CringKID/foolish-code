#include <algorithm>
#include <iostream>
#include <random>

using namespace std;
mt19937 Rand(19491001);

template <typename T, int kMaxN>
struct FHQ_Treap {
  struct Node {
    int l, r, size;
    unsigned key;
    T val;
    bool rev;
  } tr[kMaxN << 5];
  int root, tot, x, y, z;
  int node (T val) {
    tr[++tot] = {0, 0, 1, Rand (), val, false};
    return tot;
  }
  void pushup (int x) {
    tr[x].size = tr[tr[x].l].size + tr[tr[x].r].size + 1;
  }
  void pushdown (int x) {
    swap (tr[x].l, tr[x].r);
    tr[tr[x].l].rev ^= 1, tr[tr[x].r].rev ^= 1;
    tr[x].rev = false;
  }
  void split (int rt, int size, int &x, int &y) {
    if (!rt) {
      x = y = 0;
    } else {
      if (tr[rt].rev) {
        pushdown (rt);
      }
      if (tr[tr[rt].l].size < size) {
        x = rt, split (tr[rt].r, size - tr[tr[rt].l].size - 1, tr[rt].r, y);
      } else {
        y = rt, split (tr[rt].l, size, x, tr[rt].l);
      }
      pushup (rt);
    }
  }
  int merge (int x, int y) {
    if (!x || !y) {
      return x + y;
    } else {
      if (tr[x].key < tr[y].key) {
        if (tr[y].rev) {
          pushdown (y);
        }
        tr[y].l = merge (x, tr[y].l);
        pushup (y);
        return y;
      } else {
        if (tr[x].rev) {
          pushdown (x);
        }
        tr[x].r = merge (tr[x].r, y);
        pushup (x);
        return x;
      }
    }
  }
  void reverse (int l, int r) {
    split (root, l - 1, x, y), split (y, r - l + 1, y, z);
    tr[y].rev ^= 1;
    root = merge (x, merge (y, z));
  }
  void print (int x) {
    if (!x) {
      return ;
    }
    if (tr[x].rev) {
      pushdown (x);
    }
    print (tr[x].l);
    cout << tr[x].val << ' ';
    print (tr[x].r);
  }
};
FHQ_Treap <int, int (1e5 + 5)> fhq;
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  int n, m; cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    fhq.root = fhq.merge (fhq.root, fhq.node (i));
  }
  for (int i = 1, l, r; i <= m; i++) {
    cin >> l >> r;
    fhq.reverse (l, r);
  }
  fhq.print (fhq.root);
  return 0;
}