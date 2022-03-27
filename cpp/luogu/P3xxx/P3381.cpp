#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;
const int kMaxN = 5e3 + 5, kMaxM = 5e4 + 5;

int n, m, s, t, a, b, c, d, sum1, sum2, tot = 1, head[kMaxN], pos[kMaxN], fa[kMaxN], dis[kMaxN], in[kMaxN], flow[kMaxN];
struct Edge {
  int to, l, c, dis;
} edge[kMaxM << 1];
void add (int a, int b, int c, int d) {
  edge[++tot] = {b, head[a], c, d}, head[a] = tot;
  edge[++tot] = {a, head[b], 0, -d}, head[b] = tot;
}
bool spfa() {
  memset (dis, 0x3f, sizeof (dis));
  memset (in, 0, sizeof (in));
  memset (flow, 0x3f, sizeof (flow));
  queue <int> que; que.push (s), dis[s] = 0;
  while (!que.empty ()) {
    int u = que.front ();
    que.pop();
    for (int i = head[u]; i; i = edge[i].l) {
      int v = edge[i].to, di = edge[i].dis, c = edge[i].c;
      if (c && dis[v] > dis[u] + di) {
        dis[v] = dis[u] + di, pos[v] = i;
        fa[v] = u, flow[v] = min (c, flow[u]);
        if (!in[v]) {
          que.push (v);
          in[v] = 1;
        }
      }
    }
    in[u] = 0;
  }
  return flow[t] != flow[s];
}
int main() {
  cin >> n >> m >> s >> t;
  for (int i = 1; i <= m; i++) {
    cin >> a >> b >> c >> d;
    add (a, b, c, d);
  }
  while (spfa ()) {
    sum1 += flow[t], sum2 += flow[t] * dis[t];
    for (int u = t; u != s; u = fa[u]) {
      edge[pos[u]].c -= flow[t];
      edge[pos[u] ^ 1].c += flow[t];
    }
  }
  cout << sum1 << ' ' << sum2 << '\n';
  return 0;
}