#include <bits/stdc++.h>

using namespace std;

const int maxn = 2e4 + 5, maxm = 605;

int n, m, dp[maxn][maxm], a[maxn];

int main() {
  scanf("%d %d", &n, &m);
  for (register int i = 1; i <= n; i++) scanf("%d", &a[i]);
  dp[1][1] = a[1];
  for (register int i = 1; i <= n; i++)
    for (register int j = 0; j <= min(i, m); j++) {
      if (!j)
        dp[i][0] = max(dp[i - 1][0], dp[i][0]);
      else
        dp[i + j][0] = max(dp[i + j][0], dp[i][j]);
      dp[i + 1][j + 1] = max(dp[i + 1][j + 1], dp[i][j] + a[i + 1]);
    }
  printf("%d\n", dp[n][0]);
  return 0;
}