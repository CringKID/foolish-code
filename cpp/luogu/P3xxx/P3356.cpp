#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;
using ll = long long;
const int kMaxN = 2.6e3 + 5, kMaxM = kMaxN * 4, kInf = 1e9;

struct Edge {
  int to, next, flow, cost, tag;
} edge[kMaxM << 1];
int n, m, k, s, t, tot = 1, head[kMaxN], cnt1, cnt2, dist[kMaxN], maxflow, mincost, nhead[kMaxN], num[55][55], mmap[55][55];
bool vis[kMaxN];
void add (int from, int to, int flow, int cost, int tag) {
  edge[++tot] = {to, head[from], flow, cost, tag}, head[from] = tot;
  edge[++tot] = {from, head[to], 0, -cost, tag}, head[to] = tot;
}
bool SPFA () {
  fill (dist, dist + cnt2 * 2 + 2, kInf);
  for (int i = 0; i <= cnt2 * 2 + 2; i++) {
    dist[i] = kInf, nhead[i] = head[i], vis[i] = false;
  }
  queue <int> que; que.push (s), dist[s] = 0, vis[s] = 1;
  while (!que.empty ()) {
    int from = que.front (); que.pop (), vis[from] = false;
    for (int i = head[from]; i; i = edge[i].next) {
      int to = edge[i].to;
      if (edge[i].flow && dist[to] > dist[from] + edge[i].cost) {
        dist[to] = dist[from] + edge[i].cost;
        if (!vis[to]) {
          que.push (to), vis[to] = true;
        }
      }
    }
  }
  return dist[t] != dist[0];
}
int DFS (int x, int cur) {
  if (x == t) {
    return cur;
  }
  vis[x] = true;
  int rec = 0;
  for (int i = nhead[x]; i && cur; i = edge[i].next) {
    nhead[x] = i;
    int to = edge[i].to;
    if (!vis[to] && edge[i].flow && (dist[to] == dist[x] + edge[i].cost)) {
      int tmp = DFS (to, min (cur, edge[i].flow));
      if (tmp) {
        edge[i].flow -= tmp;
        edge[i ^ 1].flow += tmp;
        rec += tmp, cur -= tmp;
        mincost += edge[i].cost * tmp;
      }
    }
  }
  vis[x] = false;
  return rec;
}
bool DFS2 (int x, int cur) {
  if (cur - cnt2 == num[n][m]) {
    return true;
  }
  for (int i = head[cur]; i; i = edge[i].next) {
    int to = edge[i].to;
    if (edge[i ^ 1].flow > 0 && to <= cnt2 && edge[i].tag) {
      edge[i ^ 1].flow--;
      cout << x << ' ' << edge[i].tag - 1 << '\n';
      if (DFS2 (x, to + cnt2)) {
        return true;
      }
    }
  }
  return false;
}

int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> k >> m >> n;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      cin >> mmap[i][j];
      num[i][j] = ++cnt1;
    }
  }
  cnt2 = num[n][m], s = cnt2 * 2 + 1, t = cnt2 * 2 + 2;
  if (~mmap[1][1]) {
    add (s, num[1][1], k, 0, 0);
  }
  if (~mmap[n][m]) {
    add (num[n][m] + cnt2, t, k, 0, 0);
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (mmap[i][j] == 2) {
        add (num[i][j], num[i][j] + cnt2, 1, -1, 0);
      }
      if (mmap[i][j] != 1) {
        add (num[i][j], num[i][j] + cnt2, kInf, 0, 0);
      }
      if (mmap[i + 1][j] != 1 && num[i + 1][j]) {
        add (num[i][j] + cnt2, num[i + 1][j], kInf, 0, 1);
      }
      if (mmap[i][j + 1] != 1 && num[i][j + 1]) {
        add (num[i][j] + cnt2, num[i][j + 1], kInf, 0, 2);
      }
    }
  }
  while (SPFA ()) {
    maxflow += DFS (s, kInf);
  }
  for (int i = 1; i <= k; i++) {
    DFS2 (i, num[1][1] + cnt2);
  }
  return 0;
}