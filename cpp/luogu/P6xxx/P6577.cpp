#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
using ll = long long;
const ll kMaxN = 505, kInf = 1e18;

bool visx[kMaxN], visy[kMaxN];
ll n, m, valx[kMaxN], valy[kMaxN], edge[kMaxN][kMaxN], arr[kMaxN], belong[kMaxN], pre[kMaxN];
void findpath (ll from) {
  ll x, y = 0, cur = 0, delta;
  memset (pre, 0, sizeof (pre));
  for (int i = 1; i <= n; i++) {
    arr[i] = kInf;
  }
  belong[y] = from;
  for ( ; true; ) {
    x = belong[y], delta = kInf, visy[y] = 1;
    for (int i = 1; i <= n; i++) {
      if (visy[i]) {
        continue;
      }
      if (arr[i] > valx[x] + valy[i] - edge[x][i]) {
        arr[i] = valx[x] + valy[i] - edge[x][i], pre[i] = y;
      }
      if (arr[i] < delta) {
        delta = arr[i], cur = i;
      }
    }
    for (int i = 0; i <= n; i++) {
      if (visy[i]) {
        valx[belong[i]] -= delta, valy[i] += delta;
      } else {
        arr[i] -= delta;
      }
      // visy[i] ? (valx[belong[i]] -= delta, valy[i] += delta) : (arr[i] -= delta);
    }
    y = cur;
    if (belong[y] == -1) {
      break;
    }
  }
  while (y) {
    belong[y] = belong[pre[y]], y = pre[y];
  }
}
ll KM () {
  memset (belong, -1, sizeof (belong)), memset (valx, 0, sizeof (valx)), memset (valy, 0, sizeof (valy));
  for (ll i = 1; i <= n; i++) {
    memset (visy, 0, sizeof (visy)), findpath (i);
  }
  ll rec = 0;
  for (ll i = 1; i <= n; i++) {
    if (belong[i] != -1) {
      rec += edge[belong[i]][i];
    }
  }
  return rec;
}
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n >> m;
  for (ll i = 1; i <= n; i++) {
    for (ll j = 1; j <= n; j++) {
      edge[i][j] = -kInf;
    }
  }
  for (ll i = 1; i <= m; i++) {
    ll from, to, val;
    cin >> from >> to >> val;
    edge[from][to] = val;
  }
  cout << KM () << '\n';
  for (ll i = 1; i <= n; i++) {
    cout << belong[i] << ' ';
  }
  return 0;
}