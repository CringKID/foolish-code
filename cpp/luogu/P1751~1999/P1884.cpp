#include <algorithm>
#include <iostream>

using namespace std;

const int maxn = 1e3 + 5;

long long n, x[maxn], y[maxn], x2[maxn], y2[maxn], side[maxn << 1], ans;

int a[maxn];

int main() {
  scanf("%lld", &n);
  for (register int i = 0; i < n; i++) scanf("%lld %lld %lld %lld", &x[i], &y[i], &x2[i], &y2[i]), side[i << 1] = x[i], side[i << 1 | 1] = x2[i];
  sort(side, side + (n << 1));
  for (register int i = 1, m; i < (n << 1); i++) {
    if (side[i - 1] == side[i]) continue;
    m = 0;
    for (register int j = 0; j < n; j++)
      if (x[j] <= side[i - 1] && side[i] <= x2[j]) a[m++] = j;
    sort(a, a + m, [](int a, int b) { return y[a] > y[b]; });
    register long long h = y[a[0]], d = y2[a[0]], w = side[i] - side[i - 1];
    for (register int j = 1, tmp; j < m; j++) {
      tmp = a[j];
      if (y[tmp] > d)
        ans += (h - y[tmp]) * w, h = y[tmp];
      else
        ans += (h - d) * w, h = y[tmp];
      d = min(d, y2[tmp]);
    }
    ans += (h - d) * w;
  }
  printf("%lld\n", ans);
  return 0;
}