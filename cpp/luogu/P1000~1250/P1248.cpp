#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e3 + 5;

int n, x, y, ans;

struct node {
  int x, y, opt;
} a[maxn];

inline bool cmp(node n1, node n2) { return min(n1.x, n2.y) != min(n1.y, n2.x) ? min(n1.x, n2.y) < min(n1.y, n2.x) : n1.y < n2.y; }

int main() {
  scanf("%d", &n);
  for (register int i = 1; i <= n; i++) scanf("%d", &a[i].x), a[i].opt = i;
  for (register int i = 1; i <= n; i++) scanf("%d", &a[i].y);

  sort(a + 1, a + n + 1, cmp);

  for (register int i = 1; i <= n; i++) x += a[i].x, y = max(x, y) + a[i].y;

  printf("%d\n", y);
  for (register int i = 1; i <= n; i++) printf("%d ", a[i].opt);

  return 0;
}