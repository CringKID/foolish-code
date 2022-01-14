#include <bits/stdc++.h>
using namespace std;
int n, m, dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
bool vis[15][15];
long long ans;
void dfs(int x, int y) {
  if (x < 1 || x >= n || y < 1 || y >= m) {
    ans++;
    return;
  }
  vis[x][y] = true;
  for (register int i = 0; i <= 3; i++)
    if (!vis[x + dir[i][0]][y + dir[i][1]]) dfs(x + dir[i][0], y + dir[i][1]);
  vis[x][y] = false;
}
int main() {
  scanf("%d %d", &n, &m);
  for (register int i = 1; i < m; i++) {
    vis[0][i - 1] = 0, vis[0][i] = 1;
    dfs(1, i);
  }
  vis[0][m - 1] = 0;
  for (register int i = 1; i < n; i++) {
    vis[i - 1][0] = 0, vis[i][0] = 1;
    dfs(i, 1);
  }
  printf("%lld\n", ans);
  return 0;
}