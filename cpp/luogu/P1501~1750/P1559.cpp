#include <bits/stdc++.h>

using namespace std;

const int maxn = 25;

int p[maxn][maxn], q[maxn][maxn], n, Ans[maxn], ans;
bool vis[maxn];

void dfs(int x, int Val) {
  if (x > n) {
    ans = max(ans, Val);
    return;
  }

  int val = 0;
  for (int i = x; i <= n; i++) val += Ans[i];
  if (Val + val < ans) return;

  for (int i = 1; i <= n; i++)
    if (!vis[i]) vis[i] = true, dfs(x + 1, Val + p[x][i] * q[i][x]), vis[i] = false;
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++) scanf("%d", &p[i][j]);
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++) scanf("%d", &q[i][j]);

  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++) Ans[i] = max(Ans[i], p[i][j] * q[j][i]);
  dfs(1, 0);

  return printf("%d\n", ans) & 0;
}