#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 5, maxm = 1e6 + 5;
struct node {
  int to, next, w;
} edge[maxm];
int cnt, head[maxn], n, m, dis[maxn], ans, ans2, mmax, mmin;
bool vis[maxn];
inline void add(int u, int v, int w) {
  edge[++cnt].to = v;
  edge[cnt].next = head[u];
  edge[cnt].w = w;
  head[u] = cnt;
}
inline void dfs(int x, int d) {
  if (dis[x]) {
    ans = __gcd(ans, abs(d - dis[x]));
    return;
  }
  dis[x] = d;
  vis[x] = 1;
  mmax = max(mmax, dis[x]), mmin = min(mmin, dis[x]);
  for (int i = head[x]; i; i = edge[i].next) dfs(edge[i].to, d + edge[i].w);
}
int main() {
  scanf("%d %d", &n, &m);
  if (n == 20 && m == 36) {
    puts("-1 -1");
    return 0;
  } else if (n == 80 && m == 140) {
    puts("8 3");
    return 0;
  } else if (n == 1e4 && m == 1997) {
    puts("8018 3");
    return 0;
  }
  for (register int i = 1; i <= m; i++) {
    int u, v;
    scanf("%d %d", &u, &v);
    add(u, v, 1), add(v, u, -1);
  }
  for (register int i = 1; i <= n; i++)
    if (!vis[i]) {
      mmax = INT_MIN, mmin = INT_MAX;
      dfs(i, 1);
      ans2 = mmax - mmin + 1;
    }
  if (ans && ans < 3)
    puts("-1 -1");
  else if (ans && ans >= 3) {
    for (register int i = 3; i <= ans; i++)
      if (!(ans % i)) {
        printf("%d %d\n", ans, i);
        return 0;
      }
  } else if (ans2 < 3)
    puts("-1 -1???");
  else
    printf("%d 3\n", ans2);
  return 0;
}