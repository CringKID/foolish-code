#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>

using namespace std;
const int kMaxN = 305, kMaxM = 55, kInf = 0x3f3f3f3f;

struct Edge {
  int to, next, x, val, opt;
} edge[kMaxN * kMaxM * 2 + kMaxN + kMaxN];
int n, m, S, T, tot, cnt, s1, s2, t1, t2, disum, head[kMaxN], nhead[kMaxN], ind[kMaxN], outd[kMaxN], deg[kMaxN], dis[kMaxN];
bool vis[kMaxN];
void add(int u, int v, int x, int y) {
  edge[++cnt] = {v, head[u], x, y, cnt + 1};
  head[u] = cnt;
  edge[++cnt] = {u, nhead[v], 0, -y, cnt - 1};
  nhead[v] = cnt;
}
bool SPFA() {
	memset (deg, 0x7f, sizeof (deg)), memset (dis, 0x7f, sizeof (dis)), memcpy (nhead, head, sizeof (nhead));
  deg[S] = 0, dis[S] = 0;
  queue <int> q;
  q.push (S), vis[S] = true;
  while (!q.empty()) {
    int now = q.front (); q.pop ();
    for (int i = head[now]; i; i = edge[i].next) {
      if (edge[i].x && dis[edge[i].to] > dis[now] + edge[i].val) {
        dis[edge[i].to] = dis[now] + edge[i].val;
        deg[edge[i].to] = deg[now] + 1;
        if (!vis[edge[i].to]) {
          vis[edge[i].to] = true;
          q.push (edge[i].to);
        }
      }
    }
    vis[now] = false;
  }
  return dis[T] != dis[0];
}
int DFS (int x, int cur) {
  if (x == T) {
    return cur;
  }
  int sum = 0;
  for (int i = nhead[x]; i; i = edge[i].next) {
    if (edge[i].x && deg[edge[i].to] == deg[x] + 1 && dis[edge[i].to] == dis[x] + edge[i].val) {
      int to = DFS (edge[i].to, min (cur - sum, edge[i].x));
      if (to) {
        edge[i].x -= to;
        edge[edge[i].opt].x += to;
        sum += to;
        if (sum == cur) {
          return cur;
        }
      }
    }
  }
  if (sum != cur) {
    dis[x] = -1;
  }
  return sum;
}
int Dinic () {
  int rec = 0;
  while (SPFA ()) {
    rec += DFS (S, kInf) * dis[T];
  }
  return rec;
}
int main() {
	ios :: sync_with_stdio (false);
	cin.tie (0), cout.tie (0);

	cin >> n;
  tot = n, s1 = 1, t1 = ++tot, s2 = ++tot, t2 = ++tot;
  for (int i = 1, k, b, t; i <= n; i++) {
		cin >> k;
    for (int j = 1; j <= k; j++) {
			cin >> b >> t;
      add (i, b, kInf, t);
      outd[i] += 1;
      ind[b] += 1;
      disum += 1 * t;
    }
  }
  for (int i = 2; i <= n; i++) {
    add (i, t1, kInf, 0);
  }
  for (int i = 1; i <= n; i++) {
    if (ind[i] > outd[i]) {
			add (s2, i, ind[i] - outd[i], 0);
		}
    if (outd[i] > ind[i]) {
			add (i, t2, outd[i] - ind[i], 0);
		}
  }
  add (t1, s1, kInf, 0), S = s2, T = t2;
	cout << disum + Dinic () << '\n';
  return 0;
}