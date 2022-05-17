#include <iostream>
#include <algorithm>
#include <random>

using namespace std;
mt19937 Rand (19491001);

template <typename T, int kMaxN> 
class FHQ_Treap {
private :
  struct Node {
    int l, r, size;
    unsigned key;
    T val;
  } tr[kMaxN << 5];
  int root, tot;
  int node (T val) {
    tr[++tot] = {0, 0, 1, Rand (), val};
    return tot;
  }
  void pushup (int x) {
    tr[x].size = tr[tr[x].l].size + tr[tr[x].r].size + 1;
  }
  void split (int rt, T val, int &x, int &y) {
    if (!rt) {
      x = y = 0;
    } else {
      if (tr[rt].val > val) {
        y = rt, split (tr[rt].l, val, x, tr[rt].l);
      } else {
        x = rt, split (tr[rt].r, val, tr[rt].r, y);
      }
      pushup (rt);
    }
  }
  int merge (int x, int y) {
    if (!x || !y) {
      return x + y;
    } else {
      if (tr[x].key < tr[y].key) {
        tr[y].l = merge (x, tr[y].l);
        pushup (y);
        return y;
      } else {
        tr[x].r = merge (tr[x].r, y);
        pushup (x);
        return x;
      }
    }
  }
  int x, y, z, ans;
public :
  void insert (T val) {
    split (root, val, x, y);
    root = merge (x, merge (node (val), y));
  }
  void remove (T val) {
    split (root, val, x, z), split (x, val - 1, x, y);
    y = merge (tr[y].l, tr[y].r);
    root = merge (merge (x, y), z);
  }
  int findrank (T val) {
    split (root, val - 1, x, y);
    ans = tr[x].size + 1, root = merge (x, y);
    return ans;
  }
  T rankfind (int rank) {
    for (x = root; x; ) {
      if (tr[tr[x].l].size + 1 == rank) {
        break;
      } else if (tr[tr[x].l].size >= rank) {
        x = tr[x].l;
      } else {
        rank -= tr[tr[x].l].size + 1;
        x = tr[x].r;
      }
    }
    return tr[x].val;
  }
  int pre (T val) {
    split (root, val - 1, x, y);
    for (z = x; tr[z].r; z = tr[z].r) {
    }
    ans = tr[z].val, root = merge (x, y);
    return ans;
  }
  int post (T val) {
    split (root, val, x, y);
    for (z = y; tr[z].l; z = tr[z].l) {
    }
    ans = tr[z].val, root = merge (x, y);
    return ans;
  }
};
FHQ_Treap <int, int (1e5 + 5)> fhq;
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  int n; cin >> n;
  for (int i = 1, opt, x; i <= n; i++) {
    cin >> opt >> x;
    if (opt == 1) {
      fhq.insert (x);
    } else if (opt == 2) {
      fhq.remove (x);
    } else if (opt == 3) {
      cout << fhq.findrank (x) << '\n';
    } else if (opt == 4) {
      cout << fhq.rankfind (x) << '\n';
    } else if (opt == 5) {
      cout << fhq.pre (x) << '\n';
    } else {
      cout << fhq.post (x) << '\n';
    }
  }
  return 0;
}