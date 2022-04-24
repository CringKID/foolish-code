#include <bits/stdc++.h>

template <class T>
inline void read(T &x) {
  x = 0;
  int f = 0;
  char ch = getchar();
  while (!isdigit(ch)) {
    f |= ch == '-';
    ch = getchar();
  }
  while (isdigit(ch)) {
    x = (x << 1) + (x << 3) + (ch ^ 48);
    ch = getchar();
  }
  x = f ? -x : x;
  return;
}

typedef unsigned long long uLL;
typedef long long LL;

struct Node {
  int pos;
  LL dis;
  friend bool operator<(const Node &a, const Node &b) {
    return a.dis > b.dis;
  }
};

struct Edge {
  int to, w;
};

std::priority_queue<Node> q;
std::vector<Edge> g[200010];
LL h[200010], d[200010];
LL ans;
int n, m;
bool vis[200010];

int main() {
  read(n), read(m);
  for (int i = 1; i <= n; ++i) read(h[i]), d[i] = 1e18;
  for (int i = 1, u, v; i <= m; ++i) {
    read(u), read(v);
    g[u].push_back((Edge){v, std::max(h[v] - h[u], 0LL)});
    g[v].push_back((Edge){u, std::max(h[u] - h[v], 0LL)});
  }
  q.push((Node){1, 0});
  d[1] = 0;
  while (!q.empty()) {
    Node now = q.top();
    q.pop();
    if (vis[now.pos]) continue;
    vis[now.pos] = true;
    for (auto i : g[now.pos]) {
      if (d[i.to] > d[now.pos] + i.w) {
        d[i.to] = d[now.pos] + i.w;
        q.push((Node){i.to, d[i.to]});
      }
    }
  }
  for (int i = 1; i <= n; ++i) ans = std::max(ans, h[1] - h[i] - d[i]);
  printf("%lld\n", ans);
  return 0;
}