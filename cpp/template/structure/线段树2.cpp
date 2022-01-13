#include <algorithm>
#include <iostream>

using namespace std;
using ll = long long;
using Pii = pair <int, int>;
using Pll = pair <ll, ll>;
const int kMaxN = 1e5 + 5, kMod = 1e9 + 7, kInf = 1e9;

struct Node {
  ll value, addtag, multag;
} tree[kMaxN << 2];
ll n, m, p;
void pushup (ll rt, ll l, ll r) {
  tree[rt].value = ((tree[rt << 1].value + tree[rt << 1 | 1].value) * tree[rt].multag + tree[rt].addtag * (r - l + 1)) % p;
}
void pushdown (ll left, ll right, ll rt) {       
  ll mid = left + right >> 1;
  tree[rt << 1].addtag = tree[rt << 1].addtag * tree[rt].multag + tree[rt].addtag;
  tree[rt << 1].value = tree[rt].multag * tree[rt << 1].value + tree[rt].addtag * (mid - left + 1);
  tree[rt << 1].multag = tree[rt << 1].multag * tree[rt].multag;
  tree[rt << 1 | 1].addtag = tree[rt << 1 | 1].addtag * tree[rt].multag + tree[rt].addtag;
  tree[rt << 1 | 1].value = tree[rt].multag * tree[rt << 1 | 1].value + tree[rt].addtag * (right - mid);
  tree[rt << 1 | 1].multag = tree[rt << 1 | 1].multag * tree[rt].multag;
  tree[rt].multag = 1, tree[rt].addtag = 0;
  tree[rt << 1].addtag %= p, tree[rt << 1].value %= p, tree[rt << 1].multag %= p;
  tree[rt << 1 | 1].addtag %= p, tree[rt << 1 | 1].value %= p, tree[rt << 1 | 1].multag %= p;
}
void build (ll left, ll right, ll rt) {
  tree[rt].multag = 1, tree[rt].addtag = 0;
  if (left == right) {
    return cin >> tree[rt].value, void ();
  }

  ll mid = left + right >> 1;
  build (left, mid, rt << 1);
  build (mid + 1, right, rt << 1 | 1);
  pushup (rt, left, right);
}

void updateadd (ll left, ll right, ll rt, ll Left, ll Right, ll addtag) {
  if (right < Left || left > Right) {
    return ;
  } else if (Left <= left && right <= Right) {
    tree[rt].value += (right - left + 1) * addtag;
    tree[rt].addtag += addtag;
    return tree[rt].value %= p, tree[rt].addtag %= p, void ();
  }

  ll mid = left + right >> 1;
  pushdown (left, right, rt);
  updateadd (left, mid, rt << 1, Left, Right, addtag);
  updateadd (mid + 1, right, rt << 1 | 1, Left, Right, addtag);
  pushup (rt, left, right);
}
void updatemul (ll left, ll right, ll rt, ll Left, ll Right, ll multag) {
  if (right < Left || left > Right) {
    return ;
  } else if (Left <= left && right <= Right) {
    tree[rt].value *= multag, tree[rt].addtag *= multag, tree[rt].multag *= multag;
    return tree[rt].value %= p, tree[rt].addtag %= p, tree[rt].multag %= p, void ();
  }

  ll mid = left + right >> 1;
  pushdown (left, right, rt);
  updatemul (left, mid, rt << 1, Left, Right, multag);
  updatemul (mid + 1, right, rt << 1 | 1, Left, Right, multag);
  pushup (rt, left, right);
}
ll query (ll left, ll right, ll rt, ll Left, ll Right) {
  if (right < Left || left > Right) {
    return 0;
  } else if (Left <= left && right <= Right) {
    return tree[rt].value % p;
  }

  ll mid = left + right >> 1, cur;
  pushdown (left, right, rt);
  cur = query (left, mid, rt << 1, Left, Right) + query (mid + 1, right, rt << 1 | 1, Left, Right);
  pushup (rt, left, right);
  return cur % p;
}

int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n >> m >> p;
  build (1, n, 1);
  for (ll i = 1, opt, x, y, k; i <= m; i++) {
    cin >> opt >> x >> y;
    if (opt == 1) {
      cin >> k;
      updatemul (1, n, 1, x, y, k);
    } else if (opt == 2) {
      cin >> k;
      updateadd (1, n, 1, x, y, k);
    } else {
      cout << (query (1, n, 1, x, y) % p + p) % p << '\n';
    }
  }
  return 0;
}