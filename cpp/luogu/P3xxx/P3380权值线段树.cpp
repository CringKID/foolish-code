#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;
using Pii = pair <int, int>;
using Pll = pair <ll, ll>;
const int kMaxN = 5e4 + 5, kMod = 1e9 + 7, kInf = 1e9;

struct Node {
  int v, l, r;
#define root(x) rt[x], 1, m
#define mid (l + r >> 1)
#define lm tr[x].l, l, mid
#define rm tr[x].r, mid + 1, r
#define lrm tag ? l : mid + 1, tag ? mid : r
} tr[kMaxN << 8];
int n, q, arr[kMaxN], opt[kMaxN], tl[kMaxN], tr_[kMaxN], k[kMaxN], sum[kMaxN << 1], m, rt[kMaxN], _v, pa[2][kMaxN], pv[2];
void Pushup (int &x) {
  tr[x].v = tr[tr[x].l].v + tr[tr[x].r].v;
}
void Update (int &x, int l, int r, int now, int v) {
  if (now < l || r < now) {
    return ;
  }
  !x && (x = ++_v);
  if (l == r) {
    tr[x].v += v;
    return ;
  }
  Update (lm, now, v), Update (rm, now, v);
  Pushup (x);
}
void Update (int &x, int v) {
  for (int i = x; i <= n; i += i & -i) {
    Update (root (i), arr[x], v);
  }
}
int Query (int l, int r, int now) {
  if (l == r) {
    return 0;
  }
  int x = 0; bool tag = mid >= now;
  for (int i = 0; i < 2; i++) {
    for (int j = 1; j <= pv[i]; j++) {
      x += tr[tr[pa[i][j]].l].v * (i ? -1 : 1);
      pa[i][j] = (tag ? tr[pa[i][j]].l : tr[pa[i][j]].r);
    }
  }
  return !tag * x + Query (lrm, now);
}
int Rank (int l, int r, int now) {
  pv[0] = pv[1] = 0;
  for (int i = r; i; i -= i & -i) {
    pa[0][++pv[0]] = rt[i];
  }
  for (int i = l - 1; i; i -= i & -i) {
    pa[1][++pv[1]] = rt[i];
  }
  return Query (1, m, now) + 1;
}
int at (int l, int r, int now) {
  if (l == r) {
    return l;
  }
  int x = 0;
  for (int i = 0; i < 2; i++) {
    for (int j = 1; j <= pv[i]; j++) {
      x += tr[tr[pa[i][j]].l].v * (i ? -1 : 1);
    }
  }
  bool tag = x >= now;
  for (int i = 0; i < 2; i++) {
    for (int j = 1; j <= pv[i]; j++) {
      pa[i][j] = (tag ? tr[pa[i][j]].l : tr[pa[i][j]].r);
    }
  }
  return at (lrm, now - !tag * x);
}
int At (int l, int r, int now) {
  pv[0] = pv[1] = 0;
  for (int i = r; i; i -= i & -i) {
    pa[0][++pv[0]] = rt[i];
  }
  for (int i = l - 1; i; i -= i & -i) {
    pa[1][++pv[1]] = rt[i];
  }
  return at (1, m, now);
}
int Pre (int l, int r, int now) {
  int rnk = Rank (l, r, now) - 1;
  return rnk ? At (l, r, rnk) : 0;
}
int Post (int l, int r, int now) {
  if (now == m) {
    return m + 1;
  }
  int rnk = Rank (l, r, now + 1);
  return rnk == r - l + 2 ? m + 1 : At (l, r, rnk);
}

//#define contest
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);
#ifdef contest
  freopen (, , stdin);
  freopen (, , stdout);
#endif

  cin >> n >> q;
  for (int i = 1; i <= n; i++) {
    cin >> arr[i], sum[++m] = arr[i]; 
  }
  for (int i = 1; i <= q; i++) {
    cin >> opt[i] >> tl[i];
    if (opt[i] != 3) {
      cin >> tr_[i];
    }
    cin >> k[i];
    if (opt[i] != 2) {
      sum[++m] = k[i];
    }
  }
  sort (sum + 1, sum + m + 1), m = unique (sum + 1, sum + m + 1) - sum - 1;
  sum[0] = -INT32_MAX, sum[m + 1] = INT32_MAX;
  for (int i = 1; i <= n; i++) {
    arr[i] = lower_bound (sum + 1, sum + m + 1, arr[i]) - sum;
    Update (i, 1);
  }
  for (int i = 1; i <= q; i++) {
    if (opt[i] != 2) {
      k[i] = lower_bound (sum + 1, sum + m + 1, k[i]) - sum;
    }
    if (opt[i] == 1) {
      cout << Rank (tl[i], tr_[i], k[i]) << '\n';
    } else if (opt[i] == 2) {
      cout << sum[At (tl[i], tr_[i], k[i])] << '\n';
    } else if (opt[i] == 3) {
      Update (tl[i], -1);
      arr[tl[i]] = k[i];
      Update (tl[i], 1);
    } else if (opt[i] == 4) {
      cout << sum[Pre (tl[i], tr_[i], k[i])] << '\n';
    } else {
      cout << sum[Post (tl[i], tr_[i], k[i])] << '\n';
    }
  }
  return 0;
}