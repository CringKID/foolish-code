#include <bits/stdc++.h>
using namespace std;
const int maxm = 5e5 + 5;
int n, m, x, y, z, k, cnt, leaves, ans = INT_MAX, dis[maxm], father[maxm], head[maxm];
bool vis[maxm];
struct road {
  int to, next, len;
} edge[maxm << 1];
void add(int from, int to, int val) {
  edge[++cnt] = ((road){to, head[from], val});
  head[from] = cnt;
}
void dfs(int f, int x) {
  father[x] = f;
  if (dis[x] > dis[k]) k = x;
  for (register int i = head[x]; i; i = edge[i].next) {
    register int y = edge[i].to;
    if (y == f || vis[y]) continue;
    dis[y] = dis[x] + edge[i].len;
    dfs(x, y);
  }
}
int main() {
  scanf("%d %d", &n, &m);
  for (register int i = 1; i < n; i++) {
    scanf("%d %d %d", &x, &y, &z);
    add(x, y, z), add(y, x, z);
  }
  dis[1] = 1;
  dfs(0, 1);
  dis[k] = 0;
  dfs(0, k);
  leaves = k;
  for (register int i = leaves, j = leaves, l = 1, r = 0; i; i = father[i]) {
    while (dis[j] - dis[i] > m) j = father[j];
    x = max(dis[leaves] - dis[j], dis[i]);
    ans = min(ans, x);
  }
  for (register int i = leaves; i; i = father[i]) vis[i] = 1;
  for (register int i = leaves; i; i = father[i]) {
    dis[i] = 0;
    k = i;
    dfs(father[i], i);
  }
  for (register int i = 1; i <= n; i++) ans = max(ans, dis[i]);
  printf("%d\n", ans);
  return 0;
}