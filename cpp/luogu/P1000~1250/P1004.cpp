#include <bits/stdc++.h>
using namespace std;
int n, a, b, c, mmap[10][10], dp[10][10][10][10];
int main() {
  scanf("%d", &n);
  for (int i = 0; i <= n; i++)
    for (int j = 0; j <= n; j++) mmap[i][j] = 0;
  while (scanf("%d %d %d", &a, &b, &c) && !(a == 0 && b == 0 & c == 0)) mmap[a][b] = c;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      for (int k = 1; k <= n; k++) {
        int l = i + j - k;
        if (l < 1 || l > n) continue;
        dp[i][j][k][l] = max(max(dp[i - 1][j][k - 1][l], dp[i - 1][j][k][l - 1]), max(dp[i][j - 1][k - 1][l], dp[i][j - 1][k][l - 1])) + mmap[i][j] + mmap[k][l];
        if (i == k && j == l) dp[i][j][k][l] -= mmap[i][j];
      }
    }
  }
  printf("%d", dp[n][n][n][n]);
  return 0;
}