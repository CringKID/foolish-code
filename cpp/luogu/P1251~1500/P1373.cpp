#include <bits/stdc++.h>

using namespace std;

const int inf = 1 << 26, maxn = 805, maxsize = 20, mod = 1e9 + 7;
typedef long long ll;

int dp[maxn][maxn][maxsize][2], n, m, p, Matrix[maxn][maxn];

int main() {
  scanf("%d %d %d", &n, &m, &p), p++;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++) scanf("%d", &Matrix[i][j]), dp[i][j][Matrix[i][j] % p][0] = 1;

  int Ans = 0;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      for (int k = 0; k <= p; k++)
        dp[i][j][k][0] = (dp[i][j][k][0] + dp[i - 1][j][(k - Matrix[i][j] + p) % p][1]) % mod, dp[i][j][k][0] = (dp[i][j][k][0] + dp[i][j - 1][(k - Matrix[i][j] + p) % p][1]) % mod,
        dp[i][j][k][1] = (dp[i][j][k][1] + dp[i - 1][j][(k + Matrix[i][j]) % p][0]) % mod, dp[i][j][k][1] = (dp[i][j][k][1] + dp[i][j - 1][(k + Matrix[i][j]) % p][0]) % mod;

  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++) Ans = (Ans + dp[i][j][0][1]) % mod;

  return printf("%d\n", Ans) & 0;
}