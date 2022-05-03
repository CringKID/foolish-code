#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;
const ll kMaxN = 1e5 + 5;

ll n, m, p, tot, root;
struct Node {
  ll sum = 0, mul = 1ll, add = 0, son[2];
} tree[kMaxN << 2];
void Push (ll x, ll add, ll mul) {
  ((tree[x].add *= mul) += add) %= p, (tree[x].mul *= mul) %= p;
}
void pushdown (ll x, ll len) {
  if (len > 1) {
  Push (x << 1, tree[x].add, tree[x].mul);
  Push (x << 1 | 1, tree[x].add, tree[x].mul);
  }
  tree[x].sum = (tree[x].sum * tree[x].mul + len * tree[x].add) % p;
  tree[x].add = 0, tree[x].mul = 1;
}
void pushup (ll x, ll len) {
  pushdown (x << 1, (len + 1) >> 1), pushdown (x << 1 | 1, len >> 1);
  tree[x].sum = (tree[x << 1].sum + tree[x << 1 | 1].sum) % p;
}
void build (ll x, ll l, ll r) {
  if (l == r) {
    cin >> tree[x].sum;
    return ;
  }
  ll mid = l + r >> 1;
  build (x << 1, l, mid);
  build (x << 1 | 1, mid + 1, r);
  pushup (x, r - l + 1);
}
void update (ll rt, ll l, ll r, ll x, ll y, ll add, ll mul) {
  pushdown (rt, r - l + 1);
  // cerr << rt << ' ' << l << ' ' << r << ' ' << x << ' ' << y << ' ' << tree[rt].sum << '\n';
  if (x <= l && r <= y || l == r) {
    Push (rt, add, mul);
    return ;
  }
  ll mid = l + r >> 1;
  if (y <= mid) {
    update (rt << 1, l, mid, x, y, add, mul);
  } else if (x > mid) {
    update (rt << 1 | 1, mid + 1, r, x, y, add, mul);
  } else {
    update (rt << 1, l, mid, x, y, add, mul);
    update (rt << 1 | 1, mid + 1, r, x, y, add, mul);
  }
  pushup (rt, r - l + 1);
}
ll query (ll rt, ll l, ll r, ll x, ll y) {
  pushdown (rt, r - l + 1); 
  if (x <= l && r <= y) {
    return tree[rt].sum;
  }
  ll mid = l + r >> 1, sum = 0;
  if (y <= mid) {
    (sum += query (rt << 1, l, mid, x, y)) %= p;
  } else if (x > mid) {
    (sum += query (rt << 1 | 1, mid + 1, r, x, y)) %= p;
  } else {
    (sum += query (rt << 1, l, mid, x, y)) %= p;
    (sum += query (rt << 1 | 1, mid + 1, r, x, y)) %= p;
  }
  return sum % p;
}
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n >> m >> p;
  build (1, 1, n);
  for (ll i = 1, opt, l, r, k; i <= m; i++) {
    cin >> opt >> l >> r;
    if (opt == 1) {
      cin >> k, update (1, 1, n, l, r, 0, k);
    } else if (opt == 2) {
      cin >> k, update (1, 1, n, l, r, k, 1);
    } else {
      cout << query (1, 1, n, l, r) << '\n';
    }
  }
  return 0;
}