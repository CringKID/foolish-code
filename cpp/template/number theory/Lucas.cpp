#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 5;
int T, n, m, p;
long long a[maxn], b[maxn];
long long lucas(int x, int y) {
  if (x < y) return 0;
  if (x < p) return b[x] * a[y] * a[x - y] % p;
  return lucas(x / p, y / p) * lucas(x % p, y % p) % p;
}
int main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%d %d %d", &n, &m, &p);
    a[0] = a[1] = b[0] = b[1] = 1;
    for (register int i = 2; i <= n + m; i++) b[i] = b[i - 1] * i % p;
    for (register int i = 2; i <= n + m; i++) a[i] = (p - p / i) * a[p % i] % p;
    for (register int i = 2; i <= n + m; i++) a[i] = a[i - 1] * a[i] % p;
    printf("%lld\n", lucas(n + m, m));
  }
  return 0;
}