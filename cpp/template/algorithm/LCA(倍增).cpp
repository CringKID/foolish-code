#include <bits/stdc++.h>
using namespace std;
inline int read() {
  int X = 0;
  bool flag = 1;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    if (ch == '-') flag = 0;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    X = (X << 1) + (X << 3) + ch - '0';
    ch = getchar();
  }
  if (flag) return X;
  return ~(X - 1);
}
const int maxn = 5e5 + 5;
struct road {
  int to, next;
} edge[maxn << 1];
int a[maxn], n, m, s, head[maxn], grand[maxn][25], depth[maxn], cnt;
void add(int x, int y) {
  edge[++cnt].to = y;
  edge[cnt].next = head[x];
  head[x] = cnt;
}
void dfs(int x, int father) {
  grand[x][0] = father;
  depth[x] = depth[father] + 1;
  for (int i = 1; i <= 20; i++)
    grand[x][i] = grand[grand[x][i - 1]][i - 1];
  for (int i = head[x]; i; i = edge[i].next)
    if (edge[i].to != father) dfs(edge[i].to, x);
}
int lca(int x, int y) {
  if (depth[x] < depth[y]) swap(x, y);
  for (int i = 20; i >= 0; i--)
    if ((1 << i) <= depth[x] - depth[y]) x = grand[x][i];
  if (x == y) return x;
  for (int i = 20; i >= 0; i--)
    if (grand[x][i] != grand[y][i]) x = grand[x][i], y = grand[y][i];
  return grand[x][0];
}
int main() {
  n = read(), m = read(), s = read();
  for (int i = 1; i < n; i++) {
    int x = read(), y = read();
    add(x, y), add(y, x);
  }
  dfs(s, 0);
  for (int i = 1; i <= m; i++) {
    int x = read(), y = read();
    printf("%d\n", lca(x, y));
  }
  return 0;
}