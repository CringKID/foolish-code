#include <bits/stdc++.h>
using namespace std;
const int maxn = 20;
int n, a[maxn], sum, num[maxn][maxn], Vis;
bool vis[maxn];
void dfs(int x, int y, int depth) {
  if (y == n + 1) {
    if (depth != sum) exit(0);
    x++;
    y = 1;
    depth = 0;
  }
  if (x == n + 1 && !Vis) {
    for (register int i = 1; i <= n; i++) {
      for (register int j = 1; j < n; j++) printf("%d ", num[i][j]);
      printf("%d\n", num[i][n]);
    }
    Vis = 1;
    exit(0);
  }
  for (register int i = 1; i <= n * n; i++)
    if (!vis[i]) {
      if (y == n && depth + a[i] != sum) continue;
      static int t;
      if (x == n) {
        t = 0;
        for (register int j = 1; j < n; j++) t += num[j][y];
        if (t + a[i] != sum) continue;
      }
      if (x == n && y == 1) {
        t = 0;
        for (register int j = 1; j < n; j++) t += num[j][n - j + 1];
        if (t + a[i] != sum) continue;
      }
      if (x == n && y == n) {
        t = 0;
        for (register int j = 1; j <= n - 1; j++) t += num[j][j];
        if (t + a[i] != sum) continue;
      }
      num[x][y] = a[i];
      vis[i] = 1;
      dfs(x, y + 1, depth + a[i]);
      vis[i] = 0;
    }
  return;
}
int main() {
  scanf("%d", &n);
  for (register int i = 1; i <= n * n; i++) scanf("%d", &a[i]), sum += a[i];
  sum /= n;
  printf("%d\n", sum);
  sort(a + 1, a + n * n + 1);
  dfs(1, 1, 0);
  return 0;
}