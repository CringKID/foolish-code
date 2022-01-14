#include <bits/stdc++.h>
using namespace std;
const int maxn = 55;
int to[maxn], w[maxn], n, dp[maxn][maxn][2], c, s[maxn], p[maxn][maxn];
inline int read() {
  int X = 0;
  bool flag = 1;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    if (ch == '-') flag = 0;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    X = (X << 1) + (X << 3) + (ch ^ 48);
    ch = getchar();
  }
  return flag ? X : ~(X - 1);
}
int main() {
  n = read(), c = read();
  for (register int i = 1; i <= n; i++) to[i] = read(), s[i] = s[i - 1] + read();
  memset(dp, 0x1f, sizeof(dp));
  dp[c][c][0] = dp[c][c][1] = 0;
  for (register int i = 1; i <= n; i++)
    for (register int j = 1; j <= n; j++) p[i][j] = s[n] - (s[j] - s[i - 1]);
  for (register int i = c; i >= 1; i--)
    for (register int j = i + 1; j <= n; j++) {
      dp[i][j][0] = min(dp[i + 1][j][0] + (to[i + 1] - to[i]) * p[i + 1][j], dp[i + 1][j][1] + (to[j] - to[i]) * p[i + 1][j]);
      dp[i][j][1] = min(dp[i][j - 1][1] + (to[j] - to[j - 1]) * p[i][j - 1], dp[i][j - 1][0] + (to[j] - to[i]) * p[i][j - 1]);
    }
  printf("%d\n", min(dp[1][n][0], dp[1][n][1]));
  return 0;
}