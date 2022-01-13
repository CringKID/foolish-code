#include <bits/stdc++.h>

using namespace std;
const int kMaxN = 2e3 + 5;

int dist[kMaxN][kMaxN], n, m, ex, ey, k, x, y, vis[kMaxN][kMaxN];
bool Judge (int nx, int ny) {
  int lft = max (nx - dist[nx][ny], 1), rght = min (nx + dist[nx][ny], n);
  for (int i = lft; i <= rght; i++) {
    int cur = dist[nx][ny] - abs (i - nx);
    if (ny - cur > 0 && !vis[i][ny - cur]) {
      ex = i, ey = ny - cur;
      return false;
    } else if (ny + cur <= m && !vis[i][ny + cur]) {
      ex = i, ey = ny + cur;
      return false;
    }
  }
  return true;
}

int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n >> m >> k;
  while (k--) {
    cin >> x >> y;
    if (!vis[x][y]) {
      cout << x << ' ' << y << '\n';
      vis[x][y] = true;
      continue;
    }
    for (int i = -1; i <= 1; i++) {
      for (int j = -1; j <= 1; j++) {
        if (x + i >= n || y + j >= m || x - i <= 0 || y - j <= 0) {
          continue;
        }
        dist[x][y] = max (dist[x][y], dist[x + i][y + j] - abs (i) - abs (j));
      }
    }
    while (Judge (x, y)) {
      dist[x][y]++;
    }
    vis[ex][ey]++;
    cout << ex << ' ' << ey << '\n';
  }
  return 0;
}