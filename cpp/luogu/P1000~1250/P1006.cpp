#include <bits/stdc++.h>
using namespace std;
int n, m, mmap[55][55], dp[51][51][51][51];
int main() {
  scanf("%d %d", &n, &m);
  for (int i = 0; i <= n; i++)
    for (int j = 0; j <= m; j++) mmap[i][j] = 0;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++) scanf("%d", &mmap[i][j]);
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      for (int k = 1; k <= n; k++) {
        int l = i + j - k;
        if (l < 1 || l > m) continue;
        if (i == k && j == l && ((i != 1 || j != 1) && (i != n || j != m))) continue;
        dp[i][j][k][l] = max(max(dp[i - 1][j][k - 1][l], dp[i][j - 1][k - 1][l]), max(dp[i - 1][j][k][l - 1], dp[i][j - 1][k][l - 1])) + mmap[i][j] + mmap[k][l];
      }
    }
  }
  printf("%d", dp[n][m][n][m]);
  return 0;
}