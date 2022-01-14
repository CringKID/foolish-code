#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 5;
struct road {
  int to, next, dis;
} edge[maxn * 5];
int n, m, b, cnt, head[maxn], a[maxn];
long long dis[maxn];
bool vis[maxn];
inline void add(int from, int to, int val) {
  edge[++cnt] = (road){to, head[from], val};
  head[from] = cnt;
  edge[++cnt] = (road){from, head[to], val};
  head[to] = cnt;
}
inline bool spfa(int mid) {
  if (a[1] > mid || a[n] > mid) return false;
  memset(dis, 0x3f, sizeof(dis));
  queue<int> q;
  q.push(1);
  vis[1] = true, dis[1] = 0;
  while (!q.empty()) {
    int from = q.front();
    q.pop();
    vis[from] = false;
    for (register int i = head[from], to, val; i; i = edge[i].next) {
      to = edge[i].to, val = edge[i].dis;
      if (a[to] > mid) continue;
      if (dis[to] > dis[from] + val) {
        dis[to] = dis[from] + val;
        if (!vis[to]) vis[to] = true, q.push(to);
      }
    }
  }
  return dis[n] < b;
}
int main() {
  scanf("%d %d %d", &n, &m, &b);
  for (register int i = 1; i <= n; i++) scanf("%d", &a[i]);
  for (register int i = 1, from, to, val; i <= m; i++) {
    scanf("%d %d %d", &from, &to, &val);
    add(from, to, val);
  }
  static int l = 0, r = INT_MAX - 1, mid, ans;
  if (!spfa(r)) {
    puts("AFK");
    return 0;
  }
  while (l <= r) {
    mid = l + r >> 1;
    if (spfa(mid)) {
      r = mid - 1;
      ans = mid;
    } else
      l = mid + 1;
  }
  printf("%d\n", ans);
  return 0;
}