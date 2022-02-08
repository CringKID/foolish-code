#include <bits/stdc++.h>
using namespace std;
#define maxn 50010
bool cant[maxn];
int N, M, K;
int last[maxn];
int dx[8] = {-3, -3, -1, -1, 1, 1, 3, 3};
int dy[8] = {-1, 1, -3, 3, -3, 3, -1, 1};
int num(int x, int y) {
  return (x - 1) * M + y;
}
int len = 0;
bool v[maxn];
int f[maxn];
struct node {
  int x, y, next;
} e[maxn * 8];
void ins(int x, int y) {
  len++;
  e[len] = {x, y, last[x]};
  last[x] = len;
}
bool dfs(int x) {
  for (int i = last[x]; i != -1; i = e[i].next) {
    int y = e[i].y;
    if (!v[y]) {
      v[y] = true;
      if (f[y] == 0 || dfs(f[y])) {
        f[y] = x;
        return true;
      }
    }
  }
  return false;
}
int main() {
  scanf("%d%d%d", &N, &M, &K);
  int x, y, cnt = 0;
  memset(last, -1, sizeof(last));
  for (int i = 1; i <= K; i++) {
    scanf("%d%d", &x, &y);
    if (cant[num(x, y)]) continue;
    cant[num(x, y)] = true;
    cnt++;
  }
  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= M; j++) {
      if (!cant[num(i, j)]) {
        int u = num(i, j);
        for (int k = 0; k < 8; k++) {
          x = dx[k] + i;
          y = dy[k] + j;
          if (x >= 1 && x <= N && y >= 1 && y <= M && !cant[num(x, y)])
            ins(u, num(x, y));
        }
      }
    }
  }
  int ans = 0;
  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= M; j++) {
      memset(v, false, sizeof(v));
      x = num(i, j);
      if (!cant[x] && dfs(x)) ans++;
    }
  }
  printf("%d", N * M - cnt - ans / 2);
  return 0;
}