#include <bits/stdc++.h>

using namespace std;

const int maxn = 5e5 + 5, maxm = 1e3 + 5, dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

inline int read() {
  register int X = 0;
  register bool flag = 1;
  register char ch = getchar();

  while ((ch < '0' || ch > '9') && ch != '-') ch = getchar();
  if (ch == '-') flag = 0, ch = getchar();

  while (ch >= '0' && ch <= '9') X = (X << 1) + (X << 3) + (ch ^ 48), ch = getchar();
  return flag ? X : ~(X - 1);
}

void write(register int X) {
  if (X < 0) putchar('-'), X = ~(X - 1);
  if (X > 9) write(X / 10);

  putchar(X % 10 + '0');
}

int n, sx, sy, ans[maxm][maxm];

bool flag[maxm][maxm], vis[maxm][maxm];

deque<pair<int, int> > q;

int main() {
  memset(ans, 0x3f, sizeof(ans));
  n = read(), sx = read(), sy = read();
  for (register int i = 1, x, y; i <= n; i++) x = read(), y = read(), flag[x][y] = 1;

  q.push_back(make_pair(sx, sy)), ans[sx][sy] = 0, vis[sx][sy] = 1;
  while (!q.empty()) {
    register int fx = q.front().first, fy = q.front().second;
    q.pop_front();
    if (fx == 0 && fy == 0) return write(ans[fx][fy]), 0;

    for (register int i = 0, dx, dy; i < 4; i++) {
      dx = fx + dir[i][0], dy = fy + dir[i][1];
      if (dx < 0 || dx > 1001 || dy < 0 || dy > 1001 || vis[dx][dy]) continue;

      vis[dx][dy] = 1, ans[dx][dy] = ans[fx][fy] + flag[dx][dy];

      if (flag[dx][dy])
        q.push_back(make_pair(dx, dy));
      else
        q.push_front(make_pair(dx, dy));
    }
  }

  return 0;
}