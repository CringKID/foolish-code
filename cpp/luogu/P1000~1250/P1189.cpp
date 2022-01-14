#include <bits/stdc++.h>
using namespace std;
const int maxn = 65, maxl = 1e3 + 5;
int r, c, n, mmap[maxn][maxn], ans[maxn][maxn], dir[5][2] = {{0, 0}, {-1, 0}, {0, 1}, {1, 0}, {0, -1}};
char st[maxn][maxn], str[maxl];
bool vis[maxn][maxn];
void dfs(int dire) {
  memset(vis, 0, sizeof(vis));
  for (register int i = 1; i <= r; i++)
    for (register int j = 1; j <= c; j++)
      if (ans[i][j] && !vis[i][j]) {
        int dx = dir[dire][0] + i, dy = dir[dire][1] + j;
        ans[i][j] = 0;
        while (mmap[dx][dy]) {
          ans[dx][dy] = 1;
          vis[dx][dy] = true;
          dx += dir[dire][0], dy += dir[dire][1];
        }
      }
}
int main() {
  scanf("%d %d", &r, &c);
  for (register int i = 1; i <= r; i++) {
    scanf("%s", st[i] + 1);
    for (register int j = 1; j <= c; j++)
      if (st[i][j] == '*')
        mmap[i][j] = 1, ans[i][j] = 1;
      else if (st[i][j] == '.')
        mmap[i][j] = 1;
      else
        mmap[i][j] = 0;
  }
  scanf("%d", &n);
  for (register int i = 1; i <= n; i++) {
    scanf("%s", str);
    if (str[0] == 'N')
      dfs(1);
    else if (str[0] == 'E')
      dfs(2);
    else if (str[0] == 'S')
      dfs(3);
    else
      dfs(4);
  }
  for (register int i = 1; i <= r; i++) {
    for (register int j = 1; j <= c; j++)
      if (ans[i][j])
        printf("*");
      else if (st[i][j] == '*')
        printf(".");
      else
        printf("%c", st[i][j]);
    printf("\n");
  }
  return 0;
}