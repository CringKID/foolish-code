#include <bits/stdc++.h>
using namespace std;
int n, m, top, fa[5000005];
struct point {
  int u, v, d;
} a[5000005], team[5000005];
long long read() {
  long long x = 0;
  char c = getchar();
  while (c < '0' || c > '9') c = getchar();
  while (c >= '0' && c <= '9') x = (x << 1) + (x << 3) + c - '0', c = getchar();
  return x;
}
int find(int x) {
  if (fa[x] != x) return fa[x] = find(fa[x]);
  return fa[x];
}
void kruskal(point a) {
  for (register int i = 1; i <= n; i++) fa[i] = i;
  team[++top] = a;
  for (register int i = top; i >= 1; i--)
    if (team[i].d < team[i - 1].d) swap(team[i], team[i - 1]);
  int k = 0, res = 0;
  for (register int i = 1; i <= top; i++) {
    int r1 = find(team[i].u), r2 = find(team[i].v);
    if (r1 != r2) {
      fa[r2] = r1;
      res += team[i].d;
    } else
      k = i;
  }
  if (k) {
    top--;
    for (int i = k; i <= top; i++) swap(team[i], team[i + 1]);
  }
  if (top != n - 1) res = -1;
  printf("%d\n", res);
  return;
}
int main() {
  n = read();
  m = read();
  for (int i = 1; i <= m; i++) a[i].u = read(), a[i].v = read(), a[i].d = read();
  for (int i = 1; i <= m; i++) kruskal(a[i]);
  return 0;
}