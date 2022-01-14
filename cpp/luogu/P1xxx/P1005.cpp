#include <bits/stdc++.h>
using namespace std;
const int MAXN = 85;
inline __int128 read() {
  __int128 X = 0;
  char ch = getchar();
  while (ch < '0' || ch > '9') ch = getchar();
  while (ch >= '0' && ch <= '9') {
    X = (X << 1) + (X << 3) + ch - '0';
    ch = getchar();
  }
  return X;
}
inline void write(__int128 x) {
  if (x > 9) write(x / 10);
  putchar(x % 10 + '0');
}
int n, m;
__int128 a[MAXN][MAXN], dp[MAXN][MAXN], ans = 0;
__int128 dps(__int128 a[]) {
  memset(dp, 0, sizeof(dp));
  for (register int len = 0; len <= m; len++)
    for (register int i = 1; i + len <= m; i++)
      dp[i][i + len] = max(2 * dp[i + 1][i + len] + 2 * a[i], 2 * dp[i][i + len - 1] + 2 * a[i + len]);
  return dp[1][m];
}
int main() {
  scanf("%d %d", &n, &m);
  for (register int i = 1; i <= n; i++)
    for (register int j = 1; j <= m; j++) a[i][j] = read();
  for (register int i = 1; i <= n; i++) ans += dps(a[i]);
  write(ans);
  return 0;
}