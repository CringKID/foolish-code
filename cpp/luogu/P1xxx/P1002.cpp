#include <bits/stdc++.h>
using namespace std;
int xp[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
int yp[8] = {1, 2, 2, 1, -1, -2, -2, -1};
long long dp[25][25];
int vis[25][25];
int main() {
  int i, j, m, n, x, y, tx, ty;
  cin >> m >> n >> x >> y;
  m++;
  n++;
  x++;
  y++;
  for (int i = 0; i < 8; i++) {
    vis[x + xp[i]][y + yp[i]] = 1;
  }
  vis[x][y] = 1;
  for (i = 1; i <= m; i++)
    for (j = 1; j <= n; j++) {
      if (i == 1 && j == 1)
        dp[i][j] = 1;
      else if (vis[i][j] == 1)
        dp[i][j] = 0;
      else
        dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
    }
  cout << dp[m][n];
  return 0;
}