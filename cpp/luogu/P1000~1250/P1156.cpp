#include <bits/stdc++.h>

using namespace std;

const int maxn = 105;

struct lj {
  int t, h, f;
} trash[maxn];

int dis, n, dp[maxn];

inline bool cmp(lj a, lj b) { return a.t < b.t; }

int main() {
  scanf("%d %d", &dis, &n);
  for (register int i = 1; i <= n; i++) scanf("%d %d %d", &trash[i].t, &trash[i].f, &trash[i].h);

  sort(trash + 1, trash + n + 1, cmp), dp[0] = 10;

  for (register int i = 1; i <= n; i++)
    for (register int j = dis; j >= 0; j--)
      if (dp[j] >= trash[i].t) {
        if (j + trash[i].h >= dis) return printf("%d\n", trash[i].t) & 0;
        dp[j + trash[i].h] = max(dp[j + trash[i].h], dp[j]), dp[j] += trash[i].f;
      }

  return printf("%d\n", dp[0]) & 0;
}