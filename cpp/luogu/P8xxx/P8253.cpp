#include <iostream>
#include <algorithm>
#include <numeric>

using namespace std;
using ll = long long;
const int kMaxN = 2e5 + 5;

ll rec, ans, ans_;
int n, m, arr[kMaxN][5], tree[kMaxN << 4], mmax, x[kMaxN], y[kMaxN], val[kMaxN], qx[kMaxN], qy[kMaxN], p[5], adx, ady;
void update (int x, int val) {
  for (x += mmax; x <= mmax << 1; x += x & -x) {
    tree[x] += val;
  }
}
int query (int x) {
  int rec = 0;
  for (x += mmax; x; x -= x & -x) {
    rec += tree[x];
  }
  return rec;
}
void solve () {
  static int idx[kMaxN], idq[kMaxN];
  iota (idx, idx + n + 1, 0), iota (idq, idq + n + 1, 0);
  sort (idx + 1, idx + n + 1, [] (int a, int b) { return x[a] < x[b]; });
  sort (idq + 1, idq + n + 1, [] (int a, int b) { return qx[a] < qx[b]; });
  int p = 1;
  for (int i = 1; i <= n; ++i) {
    int now = idq[i];
    for ( ; p <= n && x[idx[p]] <= qx[now]; update (y[idx[p]], 1), p++) {
    }
    rec += 1ll * val[now] * query (qy[now]);
  }
  fill (tree, tree + 2 * mmax + 1, 0);
}
void resolve () {
  for (int i = 1; i <= n; i++) {
    x[i] = arr[i][p[1]] - arr[i][p[0]] + adx, y[i] = arr[i][p[0]] - arr[i][p[2]] + ady;
    qx[i] = arr[i][p[0]] - arr[i][p[1]], qy[i] = arr[i][p[2]] - arr[i][p[0]];
    val[i] = arr[i][p[0]];
  }
  solve (), ans_ += rec, rec = 0;
}
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> m >> n;
  for (int i = 0; i < m; i++) {
    for (int j = 1; j <= n; j++) {
      cin >> arr[j][i];
      ans += arr[j][i];
      mmax = max (mmax, arr[j][i]);
    }
  }
  ans *= n * 2;
  if (m == 2) {
    cout << ans << '\n';
    return 0;
  }
  if (m == 3) {
    iota (p, p + 3, 0);
    do {
      adx = p[1] > p[0], ady = p[2] < p[0];
      resolve ();
    } while (next_permutation (p, p + 3));
    cout << ans - ans_ * 2 << '\n';
    return 0;
  }
  iota (p, p + 4, 0);
  do {
    adx = p[1] > p[0], ady = p[2] < p[0];
    resolve ();
  } while (next_permutation (p, p + 4));
  cout << ans - ans_ << '\n';
  return 0;
}