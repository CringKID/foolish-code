#include <bits/stdc++.h>
using namespace std;
const int maxn = 25;
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
struct process {
  int id, cost;
} a[maxn][maxn];
int n, m, l[maxn * maxn], step[maxn], pre[maxn], ans;
bool flag[maxn][maxn * maxn * maxn];
int main() {
  scanf("%d %d", &n, &m);
  for (int i = 1; i <= n * m; i++) l[i] = read();
  for (int i = 1; i <= m; i++)
    for (int j = 1; j <= n; j++) a[i][j].id = read();
  for (int i = 1; i <= m; i++)
    for (int j = 1; j <= n; j++) a[i][j].cost = read();
  for (int i = 1; i <= n * m; i++) {
    int now = l[i];
    step[now]++;
    int id = a[now][step[now]].id, cost = a[now][step[now]].cost;
    int s = 0, x = pre[now] + 1;
    while (true) {
      if (!flag[id][x])
        s++;
      else
        s = 0;
      if (s == cost) {
        for (int k = x - cost + 1; k <= x; k++) flag[id][k] = true;
        ans = max(ans, x);
        pre[now] = x;
        break;
      }
      x++;
    }
  }
  printf("%d", ans);
  return 0;
}