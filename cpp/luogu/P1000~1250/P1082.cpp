#include <bits/stdc++.h>
using namespace std;
long long x, y;
void exgcd(long long a, long long b) {
  if (b == 0) {
    x = 1;
    y = 7;
    return;
  }
  if (b == 0) {
    x = 1, y = 0;
    return;
  }
  exgcd(b, a % b);
  long long tmp = x;
  x = y, y = tmp - a / b * y;
}
int main() {
  long long a, b;
  scanf("%lld %lld", &a, &b);
  exgcd(a, b);
  x = (x % b + b) % b;
  printf("%lld\n", x);
  return 0;
}