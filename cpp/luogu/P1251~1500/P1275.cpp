#include <bits/stdc++.h>
using namespace std;
const int N = 110;
int mmap[N][N], map2[N][N], n, m, T;
bool vis[N];
void change(int mmap[]) {
  for (register int i = 1; i <= m; i++) mmap[i] ^= 1;
}
bool check(int mmap[][N], int map2[][N], int j, int k) {
  for (register int i = 1; i <= n; i++)
    if (mmap[i][j] != map2[i][k]) return false;
  return true;
}
bool dfs() {
  for (register int i = 1; i <= m; i++) {
    for (register int j = 1; j <= n; j++)
      if (mmap[j][1] != map2[j][i]) change(mmap[j]);
    for (register int j = 1; j <= m; j++) {
      bool flag = 0;
      for (register int k = 1; k <= m; k++)
        if (!vis[k]) {
          flag = check(mmap, map2, j, k);
          if (flag == 1) {
            vis[k] = true;
            break;
          }
        }
      if (flag == 0) {
        memset(vis, 0, sizeof(vis));
        break;
      }
      if (j == m) {
        memset(vis, 0, sizeof(vis));
        return true;
      }
    }
  }
  return false;
}
int main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%d %d", &n, &m);
    for (register int i = 1; i <= n; i++)
      for (register int j = 1; j <= m; j++) scanf("%d", &mmap[i][j]);
    for (register int i = 1; i <= n; i++)
      for (register int j = 1; j <= m; j++) scanf("%d", &map2[i][j]);
    if (dfs())
      puts("YES");
    else
      puts("NO");
  }
  return 0;
}