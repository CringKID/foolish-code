#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;
const int kMaxN = 1e5 + 5, kMod = 1e9 + 7, kInf = 1e9;
ll n, m, to[kMaxN << 1], fath[kMaxN], nxt[kMaxN << 1], head[kMaxN], son[kMaxN], siz[kMaxN], top[kMaxN], val[kMaxN], valt[kMaxN], tree[kMaxN << 2], tag[kMaxN << 2], tot, cnt, idx[kMaxN], dep[kMaxN];
void add (ll from, ll too) {
  to[++tot] = too, nxt[tot] = head[from], head[from] = tot;
}
void pushup (ll x) {
  tree[x] = tree[x << 1] + tree[x << 1 | 1];
}
void build (ll x, ll l, ll r) {
  tag[x] = 0;
  if (l == r) {
    tree[x] = val[l];
  } else {
    ll mid = l + r >> 1;
    build (x << 1, l, mid);
    build (x << 1 | 1, mid + 1, r);
    pushup (x);
  }
}
void pushdown (ll x, ll l, ll r) {
  ll mid = l + r >> 1;
  tag[x << 1] += tag[x];
  tag[x << 1 | 1] += tag[x];
  tree[x << 1] += tag[x] * (mid - l + 1);
  tree[x << 1 | 1] += tag[x] * (r - mid);
  tag[x] = 0;
}
ll query (ll x, ll l, ll r, ll L, ll R) {
  if (L <= l && r <= R) {
    return tree[x];
  }
  pushdown (x, l, r);
  ll ans = 0, mid = l + r >> 1;
  if (L <= mid) {
    ans += query (x << 1, l, mid, L, R);
  }
  if (mid < R) {
    ans += query (x << 1 | 1, mid + 1, r, L, R);
  }
  return ans;
}
void update (ll x, ll l, ll r, ll L, ll R, ll value) {
  if (L <= l && r <= R) {
    tree[x] += value * (r - l + 1);
    tag[x] += value;
    return ;
  }
  pushdown (x, l, r);
  ll mid = l + r >> 1;
  if (L <= mid) {
    update (x << 1, l, mid, L, R, value);
  }
  if (mid < R) {
    update (x << 1 | 1, mid + 1, r, L, R, value);
  }
  pushup (x);
}

void DFS1 (ll x, ll fa) {
  fath[x] = fa, dep[x] = dep[fa] + 1, siz[x] = 1;
  for (int i = head[x]; i; i = nxt[i]) {
    if (to[i] == fa) {
      continue;
    }
    DFS1 (to[i], x);
    siz[x] += siz[to[i]];
    if (siz[son[x]] < siz[to[i]]) {
      son[x] = to[i];
    }
  }
}
void DFS2 (ll x, ll y) {
  idx[x] = ++cnt, top[x] = y, val[cnt] = valt[x];
  if (!son[x]) {
    return ;
  }
  DFS2 (son[x], y);
  for (int i = head[x]; i; i = nxt[i]) {
    if (to[i] == fath[x] || to[i] == son[x]) {
      continue;
    }
    DFS2 (to[i], to[i]);
  }
}
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> valt[i];
  }
  for (int i = 1, from, to; i < n; i++) {
    cin >> from >> to;
    add (from, to), add (to, from);
  }
  DFS1 (1, 0), DFS2 (1, 1), build (1, 1, n);
  while (m--) {
    int opt; cin >> opt;
    if (opt == 1) {
      ll x, y; cin >> x >> y;
      update (1, 1, n, idx[x], idx[x], y);
    } else if (opt == 2) {
      ll x, y; cin >> x >> y;
      update (1, 1, n, idx[x], idx[x] + siz[x] - 1, y);
    } else if (opt == 3) {
      ll x, ans = 0; cin >> x;
      while (top[x] != 1) {
        ans += query (1, 1, n, idx[top[x]], idx[x]);
        x = fath[top[x]];
      }
      cout << ans + query (1, 1, n, 1, idx[x]) << '\n';
    }
  }
  return 0;
}