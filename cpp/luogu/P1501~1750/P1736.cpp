#include <bits/stdc++.h>

using namespace std;

const int maxn = 2.5e3 + 5;

int n, m, a[maxn][maxn], dp[maxn][maxn][2], ans;

int main() {
  scanf("%d %d", &n, &m);
  for (register int i = 1; i <= n; i++)
    for (register int j = 1; j <= m; j++) scanf("%d", &a[i][j]);

  for (register int i = 1, l, r; i <= n; i++)
    for (register int j = 1; j <= m; j++)
      if (a[i][j]) {
        l = dp[i - 1][j - 1][0] + 1, r = dp[i - 1][j + 1][1] + 1;

        for (register int k = 1; k <= dp[i - 1][j - 1][0]; k++)
          if (a[i - k][j] || a[i][j - k]) {
            l = k;
            break;
          }
        for (register int k = 1; k <= dp[i - 1][j + 1][1]; k++)
          if (a[i - k][j] || a[i][j + k]) {
            r = k;
            break;
          }

        dp[i][j][0] = l, dp[i][j][1] = r, ans = max(ans, max(l, r));
      }

  return printf("%d\n", ans) & 0;
}