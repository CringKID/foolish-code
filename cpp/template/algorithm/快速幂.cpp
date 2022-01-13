#include <bits/stdc++.h>
using namespace std;
long long b, a, p, k, ans = 1, c;
int main() {
  scanf("%d %d %d", &b, &p, &k);
  a = b;
  c = p;
  while (p > 0) {
    if (p % 2 != 0) ans = ans * b % k;
    b = b * b % k;
    p = p >> 1;
  }
  ans %= k;
  printf("%d^%d mod %d=%d", a, c, k, ans);
  return 0;
}