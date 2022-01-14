#include <bits/stdc++.h>
using namespace std;
int a[17], n, k, ans[17], mmax;
const int maxn = 5e4 + 5;
inline int DP(int t) {
  static int dp[maxn];
  dp[0] = 0;
  for (register int i = 1; i <= a[t] * n; i++) dp[i] = maxn;
  for (register int i = 1; i <= t; i++)
    for (register int j = a[i]; j <= a[t] * n; j++) dp[j] = min(dp[j], dp[j - a[i]] + 1);
  for (register int i = 1; i <= a[t] * n; i++)
    if (dp[i] > n) return i - 1;
  return a[t] * n;
}
void dfs(int depth, int maxx) {
  if (k + 1 == depth) {
    if (maxx > mmax) {
      mmax = maxx;
      for (register int i = 1; i <= depth - 1; i++) ans[i] = a[i];
    }
    return;
  }
  for (register int i = a[depth - 1] + 1; i <= maxx + 1; i++) {
    a[depth] = i;
    dfs(depth + 1, DP(depth));
  }
}
int main() {
  scanf("%d %d", &n, &k);
  dfs(1, 0);
  for (register int i = 1; i <= k; i++) printf("%d ", ans[i]);
  printf("\nMAX=%d\n", mmax);
  return 0;
}