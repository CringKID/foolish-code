#include <bits/stdc++.h>
using namespace std;
const int maxn = 45;
int dp[maxn][maxn][maxn][maxn], a[405], T[5], n, m, b;
int main() {
  scanf("%d %d", &n, &m);
  for (register int i = 1; i <= n; i++) scanf("%d", &a[i]);
  dp[0][0][0][0] = a[1];
  for (register int i = 1; i <= m; i++) scanf("%d", &b), T[b]++;
  for (register int i = 0, tmp; i <= T[1]; i++)
    for (register int j = 0; j <= T[2]; j++)
      for (register int k = 0; k <= T[3]; k++)
        for (register int t = 0; t <= T[4]; t++) {
          tmp = 1 + i * 1 + j * 2 + k * 3 + t * 4;
          if (i) dp[i][j][k][t] = max(dp[i][j][k][t], dp[i - 1][j][k][t] + a[tmp]);
          if (j) dp[i][j][k][t] = max(dp[i][j][k][t], dp[i][j - 1][k][t] + a[tmp]);
          if (k) dp[i][j][k][t] = max(dp[i][j][k][t], dp[i][j][k - 1][t] + a[tmp]);
          if (t) dp[i][j][k][t] = max(dp[i][j][k][t], dp[i][j][k][t - 1] + a[tmp]);
        }
  printf("%d\n", dp[T[1]][T[2]][T[3]][T[4]]);
  return 0;
}