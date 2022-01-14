#include <bits/stdc++.h>
using namespace std;
int sum[10] = {0, 1, 3, 6, 10, 15, 21, 28, 36, 45};
int get(int n) {
  if (n < 0) return 0;
  return n;
}
long long n, ans, a, b;
int main() {
  scanf("%lld", &n);
  a = 1;
  while (n > 0) {
    ans = ans + a * (45 * (n / 10) + sum[get(n % 10 - 1)]) + n % 10 * (b + 1);
    b += (n % 10) * a;
    a *= 10;
    n /= 10;
  }
  printf("%lld\n", ans);
  return 0;
}