#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
using ll = long long;

const ll kInf = 1e9, kMaxN = 505;
ll map[kMaxN][kMaxN], lx[kMaxN], ly[kMaxN], vx[kMaxN], vy[kMaxN], mat[kMaxN], n, m, mmin, k;
bool DFS (ll x, ll K) {
  vx[x] = K;
  for (ll y = 1; y <= n; y++) {
    if (vy[y] != K && map[x][y] != kInf) {
      ll t = lx[x] + ly[y] - map[x][y];
      if (!t) {
        vy[y] = K;
        if (!mat[y] || DFS (mat[y], K)) {
          mat[y] = x;
          return true;
        }
      } else {
        mmin = min (mmin, t);
      }
    }
  }
  return false;
}
void KM () {
  for (ll i = 1; i <= n; i++) {
    while (true) {
      mmin = kInf;
      if (DFS (i, (++k))) {
        break;
      }
      for (ll j = 1; j <= n; j++) {
        if (vx[j] == k) {
          lx[j] -= mmin;
        }
        if (vy[j] == k) {
          ly[j] += mmin;
        }
      }
    }
  }
}
int main() {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);
  cin >> n >> m;
  memset (map, kInf, sizeof (map));
  for (ll i = 1; i <= n; i++) {
    lx[i] = -kInf;
  }
  for (ll i = 0; i < m; i++) {
    ll u, v, w;
    cin >> u >> v >> w;
    map[u][v] = w;
    lx[u] = max (lx[u], w);
  }
  KM ();
  ll ans = 0;
  for (ll i = 1; i <= n; i++) {
    ans += map[mat[i]][i];
  }
  cout << ans << '\n';
  for (ll i = 1; i <= n; i++) {
    cout << mat[i] << ' ';
  }
  return 0;
}