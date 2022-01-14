#include <bits/stdc++.h>
using namespace std;
const int maxn = 1005;
int n, m, mid, ans, f, p[maxn][maxn], vis[maxn][maxn], dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
namespace func {
inline int max(int a, int b) {
  return (b & ((a - b) >> 31) | a & (~(a - b) >> 31));
}
inline int min(int a, int b) {
  return (a & ((a - b) >> 31) | b & (~(a - b) >> 31));
}
inline int read() {
  int X = 0;
  bool flag = 1;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    if (ch == '-') flag = 0;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    X = (X << 1) + (X << 3) + ch - '0';
    ch = getchar();
  }
  if (flag) return X;
  return ~(X - 1);
}
inline bool bfs(int x, int y, int maxn) {
  queue<pair<int, int> > q;
  q.push(make_pair(x, y));
  vis[x][y] = 1;
  while (!q.empty()) {
    pair<int, int> front = q.front();
    q.pop();
    for (int i = 0; i < 4; i++) {
      int dx = front.first + dir[i][0], dy = front.second + dir[i][1];
      if (dx >= 1 && dx <= n && dy >= 1 && dy <= m && !vis[dx][dy] && p[dx][dy] <= maxn) {
        vis[dx][dy] = 1;
        if (dx == n)
          return true;
        else
          q.push(make_pair(dx, dy));
      }
    }
  }
  return false;
}
}  // namespace func
int main() {
  n = func::read(), m = func::read();
  int l = 0x3f3f3f3f, r = -0x3f3f3f3f;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++) {
      p[i][j] = func::read();
      r = func::max(r, p[i][j]);
      l = func::min(l, p[i][j]);
    }
  while (l <= r) {
    mid = (l + r) / 2;
    f = 0;
    memset(vis, 0, sizeof(vis));
    if (func::bfs(1, 1, mid)) {
      r = mid - 1;
      ans = mid;
    } else
      l = mid + 1;
  }
  printf("%d", ans);
  return 0;
}