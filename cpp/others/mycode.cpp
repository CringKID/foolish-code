#include <algorithm>
#include <cstdio>
using namespace std;
const int maxn = 2e5 + 5;
int n, k, r;
int tot, head[maxn], to[maxn << 1], nxt[maxn << 1];
int du[maxn], ans[maxn];
void add(int x, int y) {
  to[++tot] = y;
  nxt[tot] = head[x];
  head[x] = tot;
}
void coloring(int x, int f, int c) {
  for (int i = head[x]; i; i = nxt[i]) {
    int y = to[i];
    if (y == f)
      continue;
    c++;
    if (c > r)
      c = 1;
    ans[(i + 1) / 2] = c;
    coloring(y, x, c);
  }
}
int main() {
  scanf("%d%d", &n, &k);
  for (int i = 1; i < n; i++) {
    int x, y;
    scanf("%d%d", &x, &y);
    add(x, y);
    add(y, x);
    du[x]++, du[y]++;
  }
  sort(du + 1, du + n + 1);
  r = du[n - k];
  coloring(1, 0, 0);
  printf("%d\n", r);
  for (int i = 1; i < n; i++)
    printf("%d ", ans[i]);
  return 0;
}
