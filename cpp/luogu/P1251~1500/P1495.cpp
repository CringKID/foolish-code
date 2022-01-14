#include <bits/stdc++.h>
using namespace std;
long long n, a[15], b[15], ans, sum;
int main() {
  scanf("%lld", &n);
  for (register int i = 1; i <= n; i++) scanf("%lld %lld", &a[i], &b[i]);
  sum = a[1], ans = b[1];
  for (register int i = 2; i <= n; i++) {
    while (ans % a[i] != b[i]) ans += sum;
    sum = __detail::__lcm(sum, a[i]);
  }
  printf("%lld\n", ans);
  return 0;
}