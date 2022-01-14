#include <bits/stdc++.h>

using namespace std;
using ll = long long;
const ll kMaxN = 3e3 + 5;

ll nx, ny, n, vis[kMaxN][kMaxN], arrx[kMaxN], arry[kMaxN], purx[kMaxN], 
  pury[kMaxN], ans;
ll findx (ll x) {
  return lower_bound (arrx + 1, arrx + arrx[0] + 1, x) - arrx;
}
ll findy (ll y) {
  return lower_bound (arry + 1, arry + arry[0] + 1, y) - arry;
}

void DFS (ll x, ll y) {
  if (vis[x][y] || x < 1 || x > arrx[0] + 1 || y < 1 || y > arry[0] + 1) {
    return ;
  }
  vis[x][y] = 2;
  DFS (x - 1, y), DFS (x, y - 1), DFS (x + 1, y), DFS (x, y + 1);
}
int main () {
  cin >> n;
  arrx[++arrx[0]] = -1, arrx[++arrx[0]] = 0, arrx[++arrx[0]] = 1;
  arry[++arry[0]] = -1, arry[++arry[0]] = 0, arry[++arry[0]] = 1;

  for (ll i = 1; i <= n; i++) {
    char opt;
    ll cur;
    cin >> opt >> cur;
    if (opt == 'R') {
      ny += cur;
    } else if (opt == 'U') {
      nx += cur;
    } else if (opt == 'L') {
      ny -= cur;
    } else if (opt == 'D') {
      nx -= cur;
    }

    purx[i] = nx, pury[i] = ny;
    arrx[++arrx[0]] = nx - 1, arrx[++arrx[0]] = nx, arrx[++arrx[0]] = nx + 1;
    arry[++arry[0]] = ny - 1, arry[++arry[0]] = ny, arry[++arry[0]] = ny + 1;
  }
  sort (arrx + 1, arrx + arrx[0] + 1), sort (arry + 1, arry + arry[0] + 1);
  arrx[0] = unique (arrx + 1, arrx + arrx[0] + 1) - arrx - 1, arry[0] = unique (arry +
    1, arry + arry[0] + 1) - arry - 1;
  for (ll i = 1; i <= n; i++) {
    ll cur1 = findx (purx[i - 1]), cur2 = findy (pury[i - 1]), cur3 = findx (purx[i]),
      cur4 = findy (pury[i]);
    if (cur1 == cur3) {
      for (ll j = min (cur2, cur4); j <= max (cur2, cur4); j++) {
        vis[cur1][j] = 1;
      }
    }
    if (cur2 == cur4) {
      for (ll j = min (cur1, cur3); j <= max (cur1, cur3); j++) {
        vis[j][cur2] = 1;
      }
    }
  }
  DFS (1, 1);
  for (ll i = 1; i <= arrx[0]; i++) {
    for (ll j = 1; j <= arry[0]; j++) {
      if (vis[i][j] != 2) {
        ans += (arrx[i] - arrx[i - 1]) * (arry[j] - arry[j - 1]);
      }
    }
  }
  cout << ans << '\n';
  return 0;
}