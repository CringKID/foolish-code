#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 5, mod = 1e5 + 3;
struct road {
  int to, next;
} edge[maxn << 1];
int n, m, dis[maxn], head[maxn], ans[maxn], cnt;
bool vis[maxn];
inline void add(int from, int to) {
  edge[++cnt] = (road){to, head[from]};
  head[from] = cnt;
  edge[++cnt] = (road){from, head[to]};
  head[to] = cnt;
}
inline void spfa() {
  memset(vis, false, sizeof(vis)), memset(dis, 0x3f, sizeof(dis));
  queue<int> q;
  q.push(1);
  vis[1] = 1, dis[1] = 0, ans[1] = 1;
  while (!q.empty()) {
    int from = q.front();
    q.pop();
    vis[from] = false;
    for (register int i = head[from], to; i; i = edge[i].next) {
      to = edge[i].to;
      if (dis[to] > dis[from] + 1) {
        dis[to] = dis[from] + 1;
        ans[to] = ans[from];
        if (!vis[to]) q.push(to), vis[to] = true;
      } else if (dis[to] == dis[from] + 1)
        ans[to] = (ans[to] + ans[from]) % mod;
    }
  }
}
int main() {
  scanf("%d %d", &n, &m);
  for (register int i = 1, from, to; i <= m; i++) {
    scanf("%d %d", &from, &to);
    add(from, to);
  }
  spfa();
  for (register int i = 1; i <= n; i++) printf("%d\n", ans[i]);
  return 0;
}