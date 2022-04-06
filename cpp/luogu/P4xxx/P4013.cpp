#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
const int kMaxN = 2e4 + 5, kMaxM = 3e5 + 5, kInf = 1e8;

int n, m, S, T, Head[kMaxN], tot, que[kMaxN], dist[kMaxN], flow[kMaxN], pre[kMaxN];
bool vis[kMaxN];
struct Edge {
  int to, next, flow, val;
} edge[kMaxM];
void add (int x, int y, int c, int d) {
  edge[tot] = {y, Head[x], c, d}, Head[x] = tot++;
  edge[tot] = {x, Head[y], 0, -d}, Head[y] = tot++;
}
int encode (int x, int y) {
  return (((m << 1) * x + x * x) >> 1) + y;
}
bool SPFA () {
  int head = 0, tail = 1;
  memset (dist, -0x3f, sizeof (dist));
  memset (flow, 0, sizeof (flow));
  que[0] = S, dist[S] = 0, flow[S] = kInf;
  while (head != tail) {
    int x = que[head++];
    if (head == kMaxN) {
      head = 0;
    }
    vis[x] = false;
    for (int i = Head[x]; ~i; i = edge[i].next) {
      int to = edge[i].to;
      if (edge[i].flow && dist[to] < dist[x] + edge[i].val) {
        dist[to] = dist[x] + edge[i].val;
        pre[to] = i;
        flow[to] = min (flow[x], edge[i].flow);
        if (!vis[to]) {
          vis[to] = true;
          que[tail++] = to;
          if (tail == kMaxN) {
            tail = 0;
          }
        }
      }
    }
  }
  return flow[T] > 0;
}
int EK () {
  int cost = 0;
  while (SPFA ()) {
    int tmp = flow[T];
    cost += dist[T] * tmp;
    for (int i = T; i != S; i = edge[pre[i] ^ 1].to) {
      edge[pre[i]].flow -= tmp;
      edge[pre[i] ^ 1].flow += tmp;
    }
  }
  return cost;
}
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> m >> n;
  memset (Head, -1, sizeof (Head));
  S = 0, T = kMaxN - 1;
  for (int i = 1; i <= n; i++) {
    for (int j = 1, x; j <= m + i - 1; j++) {
      cin >> x;
      int pos = encode (i, j);
      add (pos, 1000 + pos, 1, x);
      add (1000 + pos, encode (i + 1, j), 1, 0);
      add (1000 + pos, encode (i + 1, j + 1), 1, 0);
      if (i == 1) {
        add (S, pos, 1, 0);
      }
      if (i == n) {
        add (1000 + pos, T, 1, 0);
      }
    }
  }
  cout << EK () << '\n';
  for (int i = 0; i < tot; i += 2) {
    int y = edge[i].to, x = edge[i ^ 1].to;
    if (y == 1000 + x || y == T) {
      edge[i].flow = kInf, edge[i ^ 1].flow = 0;
    } else {
      edge[i].flow = 1, edge[i ^ 1].flow = 0;
    }
  }
  cout << EK () << '\n';
  for (int i = 0; i < tot; i += 2) {
    int x = edge[i ^ 1].to;
    if (x != S) {
      edge[i].flow = kInf, edge[i ^ 1].flow = 0;
    } else {
      edge[i].flow = 1, edge[i ^ 1].flow = 0;
    }
  }
  cout << EK () << '\n';
  return 0;
}