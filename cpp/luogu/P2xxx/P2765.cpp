#include <iostream>
#include <algorithm>
#include <queue>
#include <cstring>

using namespace std;
using ll = long long;
const int kMaxN = 1.5e5 + 5, kMaxM = kMaxN * 3, kInf = 0x7f7f7f7f;

int encode (int x) {
  return x % 2 == 0 ? x - 1 : x + 1;
}
struct node {
  int v, nxt, c;
} edge[kMaxM * 2];
int head[kMaxN], cnt, n, m, k, fa[kMaxN], s, t, d[kMaxN], cur[kMaxN];
queue <int> q;
void add(int u, int v, int c) {
  edge[++cnt] = {v, head[u], c};
  head[u] = cnt;
}
struct ship {
  int h, r, s[25];
} a[25];
int findx (int x) {
  if (fa[x] != x) {
    return fa[x] = findx (fa[x]);
  }
  return fa[x];
}
void merge (int x, int y) {
  x = findx (x), y = findx (y);
  if (x != y) {
    fa[y] = x;
  }
}
int get (int x, int day) {
  return day * (n + 2) + x;
}
bool BFS () {
  while (!q.empty ()) {
    q.pop ();
  }
  memset (d, -1, sizeof d);
  q.push (s), d[s] = 0, cur[s] = head[s];
  while (!q.empty ()) {
    int u = q.front (); q.pop();
    for (int i = head[u]; i; i = edge[i].nxt) {
      int v = edge[i].v;
      if (d[v] == -1 && edge[i].c) {
        d[v] = d[u] + 1, cur[v] = head[v];
        if (v == t) {
          return true;
        }
        q.push(v);
      }
    }
  }
  return false;
}
int DFS (int u, int limit) {
  if (u == t) {
    return limit;
  }
  int flow = 0;
  for (int i = cur[u]; i && flow < limit; i = edge[i].nxt) {
    cur[u] = i;
    int v = edge[i].v;
    if (d[v] == d[u] + 1 && edge[i].c) {
      int t = DFS (v, min (edge[i].c, limit - flow));
      if (!t) {
        d[v] = -1;
      }
      edge[i].c -= t, edge[encode (i)].c += t, flow += t;
    }
  }
  return flow;
}
ll dinic() {
  ll r = 0, flow;
  while (BFS ()) {
    while (flow = DFS (s, kInf)) {
      r += flow;
    }
  }
  return r;
}
int main() {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n >> m >> k; s = kMaxN - 1, t = kMaxN - 2;
  for (int i = 0; i <= n + 1; i++) {
    fa[i] = i;
  }
  for (int i = 1; i <= m; i++) {
    cin >> a[i].h >> a[i].r;
    for (int j = 1; j <= a[i].r; j++) {
      cin >> a[i].s[j];
      if (a[i].s[j] == -1) {
        a[i].s[j] = n + 1;
      }
      if (j > 1) {
        merge (a[i].s[j - 1], a[i].s[j]);
      }
    }
  }
  if (findx (0) != findx (n + 1)) {
    cout << 0 << '\n';
    return 0;
  }
  add (s, 0, k), add (0, s, 0), add (n + 1, t, kInf), add (t, n + 1, 0);
  int day = 1, res = 0;
  while (1) {
    add (get (n + 1, day), t, kInf), add (t, get (n + 1, day), 0);
    for (int i = 0; i <= n + 1; i++) {
      add (get (i, day - 1), get (i, day), kInf), add (get (i, day), get (i, day - 1), 0);
    }
    for (int i = 1; i <= m; i++) {
      int r = a[i].r, x = a[i].s[(day - 1) % r + 1], b = a[i].s[day % r + 1];
      add (get (x, day - 1), get (b, day), a[i].h), add (get (b, day), get (x, day - 1), 0);
    }
    res += dinic ();
    if (res >= k) {
      break;
    }
    day++;
  }
  cout << day << '\n';
  return 0;
}