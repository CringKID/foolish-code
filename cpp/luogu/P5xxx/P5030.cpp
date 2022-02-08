#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
using ll = long long;
const int kMaxN = 5e4 + 5, dir[8][2] = {{-3, -1}, {-3, 1}, {-1, -3}, {-1, 3}, {1, -3}, {1, 3}, {3, -1}, {3, 1}};

int n, m, k, tot, head[kMaxN], cur[kMaxN];
bool tag[kMaxN], vis[kMaxN];
struct Edge {
  int from, to, next;
} edge[kMaxN << 3];
void add (int from, int to) {
  edge[++tot] = {from, to, head[from]};
  head[from] = tot;
}
int encode (int x, int y) {
  return (x - 1) * m + y;
}
bool DFS (int now) {
  for (int i = head[now], to; ~i; i = edge[i].next) {
    to = edge[i].to;
    if (!vis[to]) {
      vis[to] = true;
      if (!cur[to] || DFS (cur[to])) {
        cur[to] = now;
        return true;
      }
    }
  }
  return false;
}
//#define contest
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);
#ifdef contest
  freopen (, , stdin);
  freopen (, , stdout);
#endif

  int x, y, cnt = 0;
  cin >> n >> m >> k;
  memset (head, -1, sizeof (head));
  for (int i = 1; i <= k; i++) {
    cin >> x >> y;
    if (tag[encode (x, y)]) {
      continue;
    }
    tag[encode (x, y)] = true;
    cnt++;
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (!tag[encode (i, j)]) {
        int now = encode (i, j);
        for (int k = 0; k < 8; k++) {
          x = i + dir[k][0], y = j + dir[k][1];
          if (x >= 1 && x <= n && y >= 1 && y <= m && !tag[encode (x, y)]) {
            add (now, encode (x, y));
          }
        }
      }
    }
  }
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      memset (vis, false, sizeof (vis));
      x = encode (i, j);
      if (!tag[x] && DFS (x)) {
        ans++;
      }
    }
  }
  cout << n * m - cnt - ans / 2 << '\n';
  return 0;
}