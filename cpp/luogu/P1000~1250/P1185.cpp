#include <bits/stdc++.h>
using namespace std;
int k, n, m, p, x, y;
char c[800][1600];
bool f[800][1600];
void dfs(int x, int y, int a, int b, int k, int xx, int yy) {
  if (x == n) {
    c[x][y] = 'o';
    return;
  }
  if (k == 1) {
    c[x][y] = 'o';
    int X = xx + 1, Y = (yy - 1) * 2 + 1;
    if (!f[X][Y]) dfs(x + 1, y - 1, a + 1, b, 2, X, Y);
    X = xx + 1, Y = yy * 2;
    if (!f[X][Y]) dfs(x + 1, y + 1, a + 1, b, 3, X, Y);
  } else if (k == 2) {
    c[x][y] = '/';
    if (a * 2 == b)
      dfs(x + 1, y - 1, 1, a, 1, xx, yy);
    else
      dfs(x + 1, y - 1, a + 1, b, 2, xx, yy);
  } else if (k == 3) {
    c[x][y] = 92;
    if (a * 2 == b)
      dfs(x + 1, y + 1, 1, a, 1, xx, yy);
    else
      dfs(x + 1, y + 1, a + 1, b, 3, xx, yy);
  }
}
int main() {
  scanf("%d %d", &k, &p);
  while (p--) {
    scanf("%d %d", &x, &y);
    f[x][y] = 1;
  }
  if (k == 1)
    n = m = 1, c[1][1] = 'o';
  else {
    n = 3;
    for (int i = 3; i <= k; i++) n *= 2;
    m = 6 * (1 << (k - 2)) - 1;
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= m; j++) c[i][j] = ' ';
    dfs(1, m / 2 + 1, 1, n, 1, 1, 1);
  }
  for (register int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) putchar(c[i][j]);
    putchar('\n');
  }
  return 0;
}