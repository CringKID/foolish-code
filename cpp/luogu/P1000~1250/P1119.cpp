#include <bits/stdc++.h>
using namespace std;
int f[205][205], vis[205];
int n, m, Q, t[205];
int main() {
  memset(f, 0x3f3f3f3f, sizeof(f));
  scanf("%d %d", &n, &m);
  for (int i = 0; i < n; i++) {
    scanf("%d", &t[i]);
    f[i][i] = 0;
  }
  int u, v, w;
  for (int i = 1; i <= m; i++) {
    scanf("%d %d %d", &u, &v, &w);
    f[u][v] = f[v][u] = w;
  }
  scanf("%d", &Q);
  while (Q--) {
    scanf("%d %d %d", &u, &v, &w);
    for (int k = 0; k < n; k++)
      if (t[k] <= w && !vis[k]) {
        vis[k] = 1;
        for (int i = 0; i < n; i++)
          for (int j = 0; j < n; j++)
            if (f[i][j] > f[i][k] + f[k][j])
              f[i][j] = f[i][k] + f[k][j];
      }
    if (t[u] <= w && t[v] <= w && f[u][v] < 0x3f3f3f3f)
      printf("%d\n", f[u][v]);
    else
      printf("-1\n");
  }
  return 0;
}