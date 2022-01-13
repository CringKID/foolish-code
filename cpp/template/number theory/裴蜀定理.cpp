#include <bits/stdc++.h>
using namespace std;
int main() {
  int n, ans = 0, tmp;
  scanf("%d", &n);
  for (register int i = 1; i <= n; i++) {
    scanf("%d", &tmp);
    tmp = abs(tmp);
    ans = __gcd(ans, tmp);
  }
  printf("%d\n", ans);
  return 0;
}