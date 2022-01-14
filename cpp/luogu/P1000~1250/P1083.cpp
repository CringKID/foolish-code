#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 5;
int n, m, d[maxn], l[maxn], r[maxn], s[maxn], nd[maxn], rm[maxn];
inline bool check(int x) {
  memset(s, 0, sizeof(s));
  for (int i = 1; i <= x; i++) {
    s[l[i]] += d[i];
    s[r[i] + 1] -= d[i];
  }
  for (int i = 1; i <= n; i++) {
    nd[i] = nd[i - 1] + s[i];
    if (nd[i] > rm[i]) return false;
  }
  return true;
}
int main() {
  scanf("%d %d", &n, &m);
  for (int i = 1; i <= n; i++) scanf("%d", &rm[i]);
  for (int i = 1; i <= m; i++) scanf("%d %d %d", &d[i], &l[i], &r[i]);
  if (check(m)) {
    printf("0\n");
    return 0;
  }
  int lft = 1, rght = m;
  while (lft < rght) {
    int md = (lft + rght) / 2;
    if (check(md))
      lft = md + 1;
    else
      rght = md;
  }
  printf("-1\n%d", lft);
  return 0;
}