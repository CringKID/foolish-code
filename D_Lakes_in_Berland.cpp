#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;
using Pii = pair <int, int>;
using Pll = pair <ll, ll>;
const int kMaxN = 155, kMod = 1e9 + 7, kInf = 1e9, kDir[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

char opt;
Pii P[kMaxN * kMaxN];
bool tag[kMaxN * kMaxN], sign[kMaxN * kMaxN];
int map[kMaxN][kMaxN], vis[kMaxN][kMaxN], cnt, n, m, k, tot;
bool judge (int x, int y) {
  return x >= 1 && y >= 1 && x <= n && y <= m && !vis[x][y] && map[x][y] == 1;
}
bool DFS (int x, int y) {
  vis[x][y] = cnt, P[cnt].first++;
  bool cur = false;
  for (int i = 0, dx, dy; i < 4; i++) {
    dx = x + kDir[i][0], dy = y + kDir[i][1];
    if (dx < 1 || dy < 1 || dx > n || dy > m) {
      cur = true;
    }
    if (judge (dx, dy)) {
      if (!DFS (dx, dy)) {
        cur = true;
      }
    }
  }
  return !cur;
}
//#define contest
int main () {
  // ios :: sync_with_stdio (false);
  // cin.tie (0), cout.tie (0);
#ifdef contest
  freopen (, , stdin);
  freopen (, , stdout);
#endif

  cin >> n >> m >> k;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      opt = getchar ();
      for ( ; opt != '*' && opt != '.'; opt = getchar ()) {
      }
      if (opt == '*') {
        map[i][j] = 2;
      } else if (opt == '.') {
        map[i][j] = 1;
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (map[i][j] == 1 && !vis[i][j]) {
        P[++cnt].second = cnt;
        tag[cnt] = DFS (i, j);
        if (tag[cnt]) {
          tot++;
        }
      }
    }
  }
  sort (P + 1, P + cnt + 1);
  int cur = 0, ans = 0;
  for (int i = 1; i <= cnt; i++) {
    if (cur >= tot - k) {
      break;
    }
    if (tag[P[i].second]) {
      sign[P[i].second] = true;
      cur++, ans += P[i].first;
    }
  }
  cout << ans << '\n';
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (map[i][j] == 2 || sign[vis[i][j]]) {
        cout << '*';
      } else {
        cout << '.';
      }
    }
    cout << '\n';
  }
  return 0;
}