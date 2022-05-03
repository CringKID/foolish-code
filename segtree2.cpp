#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;
const ll kMaxN = 1e5 + 5;

ll n, m, p, tot, root;
struct Node {
  ll val, add, mul, son[2];
} tr[kMaxN << 2];
ll node () {
  tr[++tot] = {0, 0, 1};
  return tot;
}
void pushup (ll x, ll l, ll r) {
  tr[x].val = ((tr[tr[x].son[0]].val + tr[tr[x].son[1]].val) % p * tr[x].mul % p + tr[x].add * (r - l + 1) % p) % p;
}
void pushdown (ll x, ll l, ll r) {
  ll lson = tr[x].son[0], rson = tr[x].son[1], mid = l + r >> 1;
  (tr[lson].add = tr[lson].add * tr[x].mul + tr[x].add) %= p;
  (tr[lson].val = tr[x].mul * tr[lson].val + tr[x].add * (mid - l + 1)) %= p;
  (tr[lson].mul = tr[lson].mul * tr[x].mul) %= p;
  (tr[rson].add = tr[rson].add * tr[x].mul + tr[x].add) %= p;
  (tr[rson].val = tr[x].mul * tr[rson].val + tr[x].add * (r - mid)) %= p;
  (tr[rson].mul = tr[rson].mul * tr[x].mul) %= p;
  tr[x].add = 0, tr[x].mul = 1;
}
void build (ll x, ll l, ll r) {
  if (l == r) {
    return cin >> tr[x].val, void ();
  }
  ll mid = l + r >> 1;
  tr[x].son[0] = node (), tr[x].son[1] = node ();
  build (tr[x].son[0], l, mid);
  build (tr[x].son[1], mid + 1, r);
  pushup (x, l, r);
}
void update (ll rt, ll l, ll r, ll x, ll y, ll add, ll mul) {
  ll lson = tr[rt].son[0], rson = tr[rt].son[1];
  if (r < x || l > y) {
    return ;
  } else if (x <= l && r <= y) {
    (tr[rt].val = tr[rt].val * mul + add * (r - l + 1)) %= p;
    (tr[rt].add = tr[rt].add * mul + add) %= p;
    (tr[rt].mul = tr[rt].mul * mul) %= p;
    return ;
  }
  ll mid = l + r >> 1;
  pushdown (rt, l, r);
  update (lson, l, mid, x, y, add, mul);
  update (rson, mid + 1, r, x, y, add, mul);
  pushup (rt, l, r);
}
ll query (ll rt, ll l, ll r, ll x, ll y) {
  if (r < x || l > y) {
    return 0;
  } else if (x <= l && r <= y) {
    return tr[rt].val % p;
  }
  ll mid = l + r >> 1, cur;
  pushdown (rt, l, r);
  cur = query (tr[rt].son[0], l, mid, x, y) + query (tr[rt].son[1], mid + 1, r, x, y);
  pushup (rt, l, r);
  return cur % p;
}
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n >> m >> p, root = node (), build (root, 1, n);
  for (ll i = 1, opt, l, r, k; i <= m; i++) {
    cin >> opt >> l >> r;
    if (opt == 1) {
      cin >> k, update (root, 1, n, l, r, 0, k);
    } else if (opt == 2) {
      cin >> k, update (root, 1, n, l, r, k, 1);
    } else {
      cout << query (root, 1, n, l, r) << '\n';
    }
  }
  return 0;
}