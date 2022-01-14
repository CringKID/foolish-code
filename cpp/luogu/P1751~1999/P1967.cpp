#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e4 + 5, inf = 0x3f3f3f3f;
struct road1 {
  int x, y, dis;
} edge1[5 * maxn];
struct road2 {
  int to, next, w;
} edge2[10 * maxn];
int cnt, n, m, head[maxn], deep[maxn], father[maxn], nfather[maxn][21], w[maxn][21];
bool vis[maxn];
void addedge(int from, int to, int w) {
  edge2[++cnt].next = head[from];
  edge2[cnt].to = to;
  edge2[cnt].w = w;
  head[from] = cnt;
}
bool cmp(road1 x, road1 y) {
  return x.dis > y.dis;
}
int root(int x) {
  if (father[x] != x) father[x] = root(father[x]);
  return father[x];
}
void kruskal() {
  sort(edge1 + 1, edge1 + m + 1, cmp);
  for (register int i = 1; i <= n; i++) father[i] = i;
  for (register int i = 1; i <= m; i++) {
    int f1 = root(edge1[i].x), f2 = root(edge1[i].y);
    if (f1 != f2) {
      father[f1] = f2;
      addedge(edge1[i].x, edge1[i].y, edge1[i].dis);
      addedge(edge1[i].y, edge1[i].x, edge1[i].dis);
    }
  }
  return;
}
void dfs(int node) {
  vis[node] = 1;
  for (int i = head[node]; i; i = edge2[i].next) {
    int to = edge2[i].to;
    if (vis[to]) continue;
    deep[to] = deep[node] + 1;
    nfather[to][0] = node;
    w[to][0] = edge2[i].w;
    dfs(to);
  }
}
int lca(int x, int y) {
  if (root(x) != root(y)) return -1;
  int ans = inf;
  if (deep[x] > deep[y]) swap(x, y);
  for (register int i = 20; i >= 0; i--)
    if (deep[nfather[y][i]] >= deep[x]) {
      ans = min(ans, w[y][i]);
      y = nfather[y][i];
    }
  if (x == y) return ans;
  for (register int i = 20; i >= 0; i--)
    if (nfather[x][i] != nfather[y][i]) {
      ans = min(ans, min(w[x][i], w[y][i]));
      x = nfather[x][i];
      y = nfather[y][i];
    }
  ans = min(ans, min(w[x][0], w[y][0]));
  return ans;
}
int main() {
  int x, y, z, q;
  scanf("%d %d", &n, &m);
  for (register int i = 1; i <= m; i++) {
    scanf("%d %d %d", &x, &y, &z);
    edge1[i].x = x;
    edge1[i].y = y;
    edge1[i].dis = z;
  }
  kruskal();
  for (register int i = 1; i <= n; i++)
    if (!vis[i]) {
      deep[i] = 1;
      dfs(i);
      nfather[i][0] = i;
      w[i][0] = inf;
    }
  for (register int i = 1; i <= 20; i++)
    for (register int j = 1; j <= n; j++) {
      nfather[j][i] = nfather[nfather[j][i - 1]][i - 1];
      w[j][i] = min(w[j][i - 1], w[nfather[j][i - 1]][i - 1]);
    }
  scanf("%d", &q);
  for (register int i = 1; i <= q; i++) {
    scanf("%d %d", &x, &y);
    printf("%d\n", lca(x, y));
  }
  return 0;
}