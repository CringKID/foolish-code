// 1514 1515 1517 1518 1519 2009 1987 1986
// 1514 1515 1517 1518 1519 2009 1987 1986
#include <stdio.h>

#include <cstring>
#include <iostream>
using namespace std;
struct ss {
  int next, to;
} s[200010];
const int inf = 1e9 + 7;
int n, q, timeclock, p, top, cnt, ans, r;
int dfn[200010], low[200010], stack[200010], instack[200010], next[200010], head[200010];
int belong[200010], money[200010], sum[200010], big[200010], rd[200010];
void add(int a, int b) {
  s[++p].next = head[a];
  s[p].to = b;
  head[a] = p;
}
void tarjan(int a) {
  dfn[a] = low[a] = ++timeclock;
  instack[a] = 1;
  stack[++top] = a;
  for (int i = head[a]; i; i = s[i].next) {
    int v = s[i].to;
    if (!dfn[v]) {
      tarjan(v);
      low[a] = min(low[a], low[v]);
    } else if (instack[v])
      low[a] = min(low[a], dfn[v]);
  }
  if (dfn[a] == low[a]) {
    cnt++;
    while (stack[top + 1] != a) {
      belong[stack[top]] = cnt;
      instack[stack[top]] = 0;
      big[cnt]++;
      sum[cnt] = min(sum[cnt], money[stack[top]]);
      top--;
    }
  }
}
int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) money[i] = 1e9 + 7;
  for (int i = 1; i <= n; i++) sum[i] = 1e9;
  scanf("%d", &q);
  for (int i = 1; i <= q; i++) {
    int u, mo;
    scanf("%d%d", &u, &mo);
    money[u] = mo;
  }
  scanf("%d", &r);
  for (int i = 1; i <= r; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    add(u, v);
  }
  for (int i = 1; i <= n; i++)
    if (!dfn[i] && money[i] != inf) tarjan(i);
  for (int i = 1; i <= n; i++)
    if (!dfn[i]) {
      printf("NO\n");
      printf("%d\n", i);
      return 0;
    }
  for (int i = 1; i <= n; i++)
    for (int j = head[i]; j; j = s[j].next)
      if (belong[i] != belong[s[j].to]) rd[belong[s[j].to]]++;
  printf("YES\n");
  for (int i = 1; i <= cnt; i++)
    if (!rd[i]) ans += sum[i];
  printf("%d\n", ans);
  return 0;
}