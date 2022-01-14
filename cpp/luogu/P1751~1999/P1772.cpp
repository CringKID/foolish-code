#include <bits/stdc++.h>
using namespace std;
const int maxn = 105, inf = 1e9;
struct road {
  int to, next, dis;
} edge[maxn * maxn];
int day, n, update, m, cnt, t, head[maxn], dis[maxn];
bool flag[maxn], vis[maxn], will[maxn][maxn];
long long SPFA[maxn][maxn], dp[maxn];
inline void add(int from, int to, int val) {
  edge[++cnt] = (road){to, head[from], val};
  head[from] = cnt;
  edge[++cnt] = (road){from, head[to], val};
  head[to] = cnt;
}
queue<int> q;
inline int spfa(int x, int y) {
  fill(dis, dis + n + 2, inf), memset(vis, false, sizeof(vis)), memset(flag, false, sizeof(flag));
  for (register int i = 1; i <= n; i++)
    for (register int j = x; j <= y; j++) flag[i] = max(flag[i], will[i][j]);
  while (!q.empty()) q.pop();
  q.push(1), dis[1] = 0, vis[1] = true;
  while (!q.empty()) {
    static int from;
    from = q.front();
    q.pop();
    vis[from] = 0;
    for (register int i = head[from], to, val; i; i = edge[i].next) {
      to = edge[i].to, val = edge[i].dis;
      if (flag[to]) continue;
      if (dis[to] > dis[from] + val) {
        dis[to] = dis[from] + val;
        if (!vis[to]) q.push(to), vis[to] = true;
      }
    }
  }
  return dis[n];
}
int main() {
  scanf("%d %d %d %d", &day, &n, &update, &m);
  for (register int i = 1, from, to, val; i <= m; i++) scanf("%d %d %d", &from, &to, &val), add(from, to, val);
  scanf("%d", &t);
  for (register int i = 1, tmp, from, to; i <= t; i++) {
    scanf("%d %d %d", &tmp, &from, &to);
    for (register int j = from; j <= to; j++) will[tmp][j] = true;
  }
  for (register int i = 1; i <= day; i++)
    for (register int j = 1; j <= day; j++) SPFA[i][j] = spfa(i, j);
  for (register int i = 1; i <= day; i++) {
    dp[i] = (long long)SPFA[1][i] * i;
    for (register int j = 1; j <= i; j++) dp[i] = min(dp[i], dp[j] + update + (long long)SPFA[j + 1][i] * (i - j));
  }
  printf("%lld\n", dp[day]);
  return 0;
}