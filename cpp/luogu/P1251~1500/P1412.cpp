#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 5;
int n, type[maxn], x[maxn];
double c, k, w, dp[maxn];
int main() {
  scanf("%d %lf %lf %lf", &n, &k, &c, &w);
  for (register int i = 1; i <= n; i++) scanf("%d %d", &type[i], &x[i]);
  for (register int i = n; i >= 1; i--)
    if (type[i] == 1)
      dp[i] = max(dp[i + 1], dp[i + 1] * (1 - 0.01 * k) + x[i]);
    else
      dp[i] = max(dp[i + 1], dp[i + 1] * (1 + 0.01 * c) - x[i]);
  printf("%.2lf\n", dp[1] * w);
  return 0;
}