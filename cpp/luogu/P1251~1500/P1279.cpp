#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e3 + 5;
int dp[maxn][maxn], len1, len2, k;
char s1[maxn], s2[maxn];
int main() {
  scanf("%s %s %d", s1 + 1, s2 + 1, &k);
  len1 = strlen(s1 + 1), len2 = strlen(s2 + 1);
  for (register int i = 1; i <= len1; i++) dp[i][0] = dp[i - 1][0] + k;
  for (register int i = 1; i <= len2; i++) dp[0][i] = dp[0][i - 1] + k;
  for (register int i = 1; i <= len1; i++)
    for (register int j = 1; j <= len2; j++)
      dp[i][j] = min(min(dp[i - 1][j], dp[i][j - 1]) + k, dp[i - 1][j - 1] + abs((int)(s1[i] - s2[j])));
  printf("%d", dp[len1][len2]);
  return 0;
}