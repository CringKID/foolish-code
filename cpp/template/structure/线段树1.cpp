#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;
using Pii = pair <int, int>;
using Pll = pair <ll, ll>;
const int kMaxN = 1e5 + 5, kMod = 1e9 + 7, kInf = 1e9;

struct Node {
  ll value, lazy;
} tree[kMaxN << 2];
ll n, m, arr[kMaxN];
void pushup (ll rt) {
  tree[rt].value = tree[rt << 1].value + tree[rt << 1 | 1].value;
}
void pushdown (ll left, ll right, ll rt) {
  if (tree[rt].lazy != 0) {
    ll mid = left + right >> 1;
    tree[rt << 1].lazy += tree[rt].lazy, tree[rt << 1 | 1].lazy += tree[rt].lazy;
    tree[rt << 1].value += (mid - left + 1) * tree[rt].lazy, tree[rt << 1 | 1].value += (right - mid) * tree[rt].lazy;
    tree[rt].lazy = 0;
  }
}

void build (ll left, ll right, ll rt) {
  if (left == right) {
    return cin >> tree[rt].value, void ();
  }
  ll mid = left + right >> 1;
  build (left, mid, rt << 1);
  build (mid + 1, right, rt << 1 | 1);
  pushup (rt);
}
void update (ll left, ll right, ll rt, ll Left, ll Right, ll tag) {
  if (right < Left || left > Right) {
    return ;
  } else if (Left <= left && right <= Right) {
    tree[rt].value += (right - left + 1) * tag;
    return tree[rt].lazy += tag, void ();
  }

  ll mid = left + right >> 1;
  pushdown (left, right, rt);
  update (left, mid, rt << 1, Left, Right, tag);
  update (mid + 1, right, rt << 1 | 1, Left, Right, tag);
  pushup (rt);
}
ll query (ll left, ll right, ll rt, ll Left, ll Right) {
  if (right < Left || left > Right) {
    return 0;
  } else if (Left <= left && right <= Right) {
    return tree[rt].value;
  }

  ll mid = left + right >> 1, cur;
  pushdown (left, right, rt);
  cur = query (left, mid, rt << 1, Left, Right) + query (mid + 1, right, rt << 1 | 1, Left, Right);
  pushup (rt);
  return cur;
}

int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n >> m;
  build (1, n, 1);
  for (ll i = 1, opt, x, y, k; i <= m; i++) {
    cin >> opt >> x >> y;
    if (opt == 1) {
      cin >> k;
      update (1, n, 1, x, y, k);
    } else {
      cout << query (1, n, 1, x, y) << '\n';
    }
  }
  return 0;
}