#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
int n, a, b, cnt, head[20010];
struct road {
  int to, next;
} r[200010];
void add(int a, int b) {
  r[++cnt].to = b;
  r[cnt].next = head[a];
  head[a] = cnt;
}
int dfn[20010], vis[20010], low[20010], tot;
void tarjan(int x, int fa) {
  int son = 0;
  dfn[x] = low[x] = ++tot;
  for (int i = head[x]; i; i = r[i].next) {
    int to = r[i].to;
    if (!dfn[to]) {
      son++;
      tarjan(to, x);
      low[x] = min(low[x], low[to]);
      if (low[to] >= dfn[x]) {
        if (fa != -1) {
          vis[x] = true;
        } else if (son >= 2) {
          vis[x] = true;
        }
      }
    } else if (fa != to) {
      low[x] = min(low[x], dfn[to]);
    }
  }
}
char temp[111111];
int main() {
  int m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; i++) {
    scanf("%d%d", &a, &b);
    add(a, b);
    add(b, a);
  }
  for (int i = 1; i <= n; i++) {
    if (!dfn[i]) {
      tarjan(i, -1);
    }
  }
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    if (vis[i] == true) {
      ans++;
    }
  }
  printf("%d\n", ans);
  for (int i = 1; i <= n; i++) {
    if (vis[i] == true) {
      cout << i << " ";
    }
    vis[i] = 0;
    dfn[i] = low[i] = 0;
    head[i] = 0;
  }
  return 0;
}