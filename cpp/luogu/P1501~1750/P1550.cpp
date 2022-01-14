#include <bits/stdc++.h>

using namespace std;

const int maxn = 305;

int n, dis[maxn], ans, cost[maxn][maxn];

bool vis[maxn];

int main() {
  scanf("%d", &n);
  for (register int i = 1; i <= n; i++) scanf("%d", &dis[i]);
  for (register int i = 1; i <= n; i++)
    for (register int j = 1; j <= n; j++) scanf("%d", &cost[i][j]);

  for (register int i = 1, pos, mmin = 1 << 30; i <= n; i++, mmin = 1 << 30) {
    for (register int j = 1; j <= n; j++)
      if (!vis[j] && dis[j] < mmin) mmin = dis[j], pos = j;

    ans += mmin, vis[pos] = 1;

    for (register int j = 1; j <= n; j++)
      if (!vis[j] && cost[pos][j] < dis[j]) dis[j] = cost[pos][j];
  }

  return printf("%d\n", ans) & 0;
}