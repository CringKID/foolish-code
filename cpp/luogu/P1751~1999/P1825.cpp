#include <bits/stdc++.h>
using namespace std;
const int N = 601, M = 180000, dx[4] = {0, 0, -1, 1}, dy[4] = {-1, 1, 0, 0};
struct node {
  int v, w, nex;
} t[M << 1];
struct strom {
  int x[3], y[3], e;
} p[26];
int las[M], len, dis[M][2];
bool vis[M][2], ys[M];
char a[N][N];
priority_queue<pair<int, pair<int, int> > > s;
inline void dijkstra(int X) {
  memset(dis, 0x3f, sizeof(dis));
  dis[X][0] = 0;
  s.push(make_pair(0, make_pair(X, 0)));
  while (!s.empty()) {
    register int x = s.top().second.first, y = s.top().second.second;
    s.pop();
    if (vis[x][y]) continue;
    vis[x][y] = 1;
    if (!y)
      for (register int i = las[x], v, w, T; i; i = t[i].nex) {
        v = t[i].v, w = t[i].w, T = ys[v];
        if (dis[v][T] > dis[x][y] + w) {
          dis[v][T] = dis[x][y] + w;
          s.push(make_pair(-dis[v][T], make_pair(v, T)));
        }
      }
    else
      for (register int i = las[x], v; i; i = t[i].nex) {
        if (t[i].w) continue;
        v = t[i].v;
        if (dis[v][0] > dis[x][1]) {
          dis[v][0] = dis[x][1];
          s.push(make_pair(-dis[v][0], make_pair(v, 0)));
        }
      }
  }
}
inline void add(int u, int v, int w = 0) {
  len++;
  t[len].v = v, t[len].w = w;
  t[len].nex = las[u], las[u] = len;
}
int main() {
  register int n, m, S, E;
  scanf("%d %d", &n, &m);
  for (register int i = 1; i <= n; i++) scanf("%s", a[i]);
  for (register int i = 1; i <= n; ++i)
    for (register int j = 1; j <= m; j++) {
      if (a[i][j - 1] == '#')
        continue;
      else if (a[i][j - 1] == '@')
        S = (i - 1) * m + j;
      else if (a[i][j - 1] == '=')
        E = (i - 1) * m + j;
      else if (a[i][j - 1] >= 'A' && a[i][j - 1] <= 'Z') {
        ys[(i - 1) * m + j] = 1;
        register int v = a[i][j - 1] - 'A', now = ++p[v].e;
        p[v].x[now] = i, p[v].y[now] = j;
      }
      for (register int k = 0, xx, yy; k < 4; k++) {
        xx = i + dx[k], yy = j + dy[k];
        if (xx > 0 && xx <= n && yy > 0 && yy <= m && a[xx][yy - 1] != '#') add((i - 1) * m + j, (xx - 1) * m + yy, 1);
      }
    }
  for (register int i = 0; i < 26; i++)
    if (p[i].e) add((p[i].x[1] - 1) * m + p[i].y[1], (p[i].x[2] - 1) * m + p[i].y[2]), add((p[i].x[2] - 1) * m + p[i].y[2], (p[i].x[1] - 1) * m + p[i].y[1]);
  dijkstra(S);
  printf("%d", dis[E][0]);
  return 0;
}