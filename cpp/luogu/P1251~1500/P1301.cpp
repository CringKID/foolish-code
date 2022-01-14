#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 5, maxm = 105, inf = 0x3f3f3f3f;
int n, m, tail = 1, head = 0, mmin = inf, ans[maxn], b[maxn], a[maxm][maxm], team[maxn][2], dir[8][2] = {{1, 0}, {0, 1}, {0, -1}, {-1, 0}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
bool vis[maxn][maxm][50];
inline void bfs() {
  do {
    head++;
    if (team[head][0] == m && team[head][1] == n) {
      mmin = min(mmin, ans[head]);
      continue;
    }
    for (register int i = 0; i < 8; i++) {
      if (i == b[head]) continue;
      int dx = team[head][0] + dir[i][0] * a[team[head][0]][team[head][1]], dy = team[head][1] + dir[i][1] * a[team[head][0]][team[head][1]];
      if (dx < 0 || dx > m || dy < 0 || dy > n || vis[team[head][0]][team[head][1]][i]) continue;
      vis[team[head][0]][team[head][1]][i] = 1;
      team[++tail][0] = dx, team[tail][1] = dy;
      ans[tail] = ans[head] + 1, b[tail] = i;
    }
  } while (head != tail);
}
int main() {
  scanf("%d %d", &n, &m);
  for (register int i = 1; i <= m; i++)
    for (register int j = 1; j <= n; j++) scanf("%d", &a[i][j]);
  team[1][0] = team[1][1] = 1;
  b[1] = 9;
  bfs();
  if (mmin != inf)
    printf("%d\n", mmin);
  else
    puts("NEVER");
  return 0;
}