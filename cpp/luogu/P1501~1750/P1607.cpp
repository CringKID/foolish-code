#include <bits/stdc++.h>

using namespace std;

const int maxn = 5e4 + 5;

int k, n, c, pre, ans, cnt, a[maxn];

struct cow {
  int s, e, m;
} ox[maxn];

int main() {
  scanf("%d %d %d", &k, &n, &c);
  for (register int i = 1; i <= k; i++) scanf("%d %d %d", &ox[i].s, &ox[i].e, &ox[i].m);
  sort(ox + 1, ox + k + 1, [](cow x, cow y) { return x.e < y.e || x.e == y.e && x.s > y.s; });
  for (register int i = 1; i <= k; i++) {
    sort(a + 1, a + c + 1, greater<int>());
    for (register int j = 1; j <= c && ox[i].m; j++)
      if (a[j] <= ox[i].s)
        ans++, a[j] = ox[i].e, ox[i].m--;
  }
  printf("%d\n", ans);
  return 0;
}