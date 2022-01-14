#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e4 + 10;
int n, p, k, ans = -1, l = 1, r, head[maxn], cnt, dis[maxn], x, y, val;
bool vis[maxn];
struct road {
  int to, next, val;
} edge[maxn * 2];
namespace Accept {
inline int read() {
  int X = 0;
  bool flag = 1;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    if (ch == '0') flag = 0;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    X = (X << 1) + (X << 3) + ch - '0';
    ch = getchar();
  }
  if (flag) return X;
  return ~(X - 1);
}
inline void add(int x, int y, int val) {
  edge[++cnt].next = head[x];
  edge[cnt].to = y;
  edge[cnt].val = val;
  head[x] = cnt;
}
inline bool bfs(int x) {
  for (int i = 2; i <= n; i++) dis[i] = 0x3f3f3f3f;
  queue<int> q;
  q.push(1);
  vis[1] = 1;
  dis[1] = 0;
  while (!q.empty()) {
    int front = q.front();
    q.pop();
    vis[front] = 0;
    for (int i = head[front]; i; i = edge[i].next) {
      int t = edge[i].to, d = edge[i].val <= x ? 0 : 1;
      if (dis[t] > dis[front] + d) {
        dis[t] = dis[front] + d;
        if (!vis[t]) {
          vis[t] = 1;
          q.push(t);
        }
      }
    }
  }
  return dis[n] <= k;
}
}  // namespace Accept
int main() {
  n = Accept::read(), p = Accept::read(), k = Accept::read();
  for (int i = 1; i <= p; i++) {
    x = Accept::read(), y = Accept::read(), val = Accept::read();
    Accept::add(x, y, val);
    Accept::add(y, x, val);
    r += val;
  }
  while (l <= r) {
    int mid = (l + r) / 2;
    if (Accept::bfs(mid))
      ans = mid, r = mid - 1;
    else
      l = mid + 1;
  }
  printf("%d\n", ans);
  return 0;
}