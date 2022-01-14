#include <bits/stdc++.h>

using namespace std;

const int maxn = 5e4 + 1;

int n, cnt1, cnt2, min1 = maxn, min2 = maxn;

int main() {
  scanf("%d", &n);
  for (register int i = 0, x, y; i < n; i++) {
    scanf("%d %d", &x, &y), cnt1 += x, cnt2 += y;
    min1 = min(min1, x), min2 = min(min2, y);
  }
  printf("%d\n", max(cnt1 + min2, cnt2 + min1));
  return 0;
}