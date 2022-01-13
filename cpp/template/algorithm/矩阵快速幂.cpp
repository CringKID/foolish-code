#include <bits/stdc++.h>
using namespace std;
long long n, k, x[999][999], ans[999][999], dx[999][999];
const int p = 1e9 + 7;
void square_multiplication_ans(int n) {
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++) {
      dx[i][j] = ans[i][j];
      ans[i][j] = 0;
    }
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
      for (int k = 1; k <= n; k++)
        ans[i][j] = (ans[i][j] + (x[i][k] * dx[k][j]) % p) % p;
  return;
}
void square_multiplication_x(int n) {
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++) {
      dx[i][j] = x[i][j];
      x[i][j] = 0;
    }
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
      for (int k = 1; k <= n; k++)
        x[i][j] = (x[i][j] + (dx[i][k] * dx[k][j]) % p) % p;
}
void square_quickpow(long long n, long long w) {
  while (w) {
    if (w % 2 == 1) square_multiplication_ans(n);
    w /= 2;
    square_multiplication_x(n);
  }
}
int main() {
  scanf("%lld %lld", &n, &k);
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++) {
      scanf("%d", &x[i][j]);
      ans[i][j] = x[i][j];
    }
  square_quickpow(n, k - 1);
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) printf("%lld ", ans[i][j]);
    printf("\n");
  }
  return 0;
}