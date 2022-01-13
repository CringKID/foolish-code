#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e4 + 5;
int ans, a[maxn], k, n, T;
int main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (register int i = 0; i < n; i++) {
      scanf("%d", &a[i]);
      ans ^= a[i];
    }
    if (!ans) {
      puts("No");
      continue;
    }
    puts("Yes");
    ans = 0;
  }
  return 0;
}