#include <bits/stdc++.h>

using namespace std;

const int maxn = 105;

int n, m, t, a[maxn][maxn], b[maxn][maxn], sx, sy, ex, ey;

int main() {
  scanf("%d %d %d", &n, &m, &t);
  for (register int i = 1; i <= n; i++)
    for (register int j = 1; j <= m; j++) {
      char ch;
      cin >> ch;
      if (ch == '*') a[i][j] = b[i][j] = -1;
    }
  scanf("%d %d %d %d", &sx, &sy, &ex, &ey);

  a[sx][sy] = b[sx][sy] = 1;

  while (t--) {
    for (register int i = 1; i <= n; i++)
      for (register int j = 1; j <= m; j++)
        if (~a[i][j])
          b[i][j] = (~a[i - 1][j] ? a[i - 1][j] : 0) + (~a[i + 1][j] ? a[i + 1][j] : 0) + (~a[i][j - 1] ? a[i][j - 1] : 0) + (~a[i][j + 1] ? a[i][j + 1] : 0);
    for (register int i = 1; i <= n; i++)
      for (register int j = 1; j <= m; j++) a[i][j] = b[i][j];
  }

  return printf("%d\n", a[ex][ey]) & 0;
}