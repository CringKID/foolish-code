#include <bits/stdc++.h>
using namespace std;
const int N = 10006, M = 100006;
int n, m, t1, t2, w1[N], w2[N], num[N], cnt = 0, head1[N], t, tot = 0, head2[N], x[N], dfn[N], low[N], ans[N], maxa = -1, rd[N], deep = 0, top = 0, v[N];
struct edge {
  int to, next;
} e[M], f[M];
inline void add(int u, int v, edge a[], int head[]) {
  a[++cnt].to = v;
  a[cnt].next = head[u];
  head[u] = cnt;
}
void tarjan(int u) {
  low[u] = dfn[u] = ++deep;
  x[++top] = u;
  v[u] = 1;
  for (int i = head1[u]; i; i = e[i].next) {
    if (!dfn[e[i].to]) {
      tarjan(e[i].to);
      low[u] = min(low[u], low[e[i].to]);
    } else if (v[e[i].to])
      low[u] = min(low[u], dfn[e[i].to]);
  }
  if (dfn[u] == low[u]) {
    num[u] = ++tot;
    v[u] = 0;
    while (x[top] != u) {
      v[x[top]] = 0;
      num[x[top]] = tot;
      --top;
    }
    --top;
  }
}
int main() {
  scanf("%d %d", &n, &m);
  for (int i = 1; i <= n; i++) scanf("%d", &w1[i]);
  for (int i = 1; i <= m; i++) {
    scanf("%d %d", &t1, &t2);
    add(t1, t2, e, head1);
  }
  for (int i = 1; i <= n; i++)
    if (!dfn[i]) tarjan(i);
  cnt = 0;
  for (int i = 1; i <= n; i++) {
    w2[num[i]] += w1[i];
    for (int j = head1[i]; j; j = e[j].next)
      if (num[i] != num[e[j].to]) {
        add(num[i], num[e[j].to], f, head2);
        ++rd[num[e[j].to]];
      }
  }
  memset(x, 0, sizeof(x));
  queue<int> q;
  cnt = 0;
  for (int i = 1; i <= tot; i++)
    if (!rd[i]) {
      x[++cnt] = i;
      q.push(i);
    }
  while (!q.empty()) {
    int tmp = q.front();
    q.pop();
    for (int i = head2[tmp]; i; i = f[i].next) {
      --rd[f[i].to];
      if (!rd[f[i].to]) x[++cnt] = f[i].to, q.push(f[i].to);
    }
  }
  for (int i = 1; i <= n; ++i) {
    t = x[i];
    ans[t] = max(ans[t], w2[t]);
    maxa = max(maxa, ans[t]);
    for (int j = head2[t]; j; j = f[j].next) ans[f[j].to] = max(ans[f[j].to], ans[t] + w2[f[j].to]);
  }
  printf("%d\n", maxa);
  return 0;
}