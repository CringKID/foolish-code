#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e3 + 5;
int a[maxn], b[maxn], ans, n, l1 = 1, l2 = 1, r1, r2;
inline int read() {
  register int X = 0;
  register char ch = getchar();
  while (ch < '0' || ch > '9') ch = getchar();
  while (ch >= '0' && ch <= '9') X = (X << 1) + (X << 3) + (ch ^ 48), ch = getchar();
  return X;
}
int main() {
  r1 = r2 = n = read();
  for (register int i = 1; i <= n; i++) a[i] = read();
  for (register int i = 1; i <= n; i++) b[i] = read();
  sort(a + 1, a + n + 1), sort(b + 1, b + n + 1);
  for (register int i = 1; i <= n; i++)
    if (a[r1] > b[r2])
      ans += 200, r1--, r2--;
    else if (a[r1] < b[r2])
      ans -= 200, l1++, r2--;
    else if (a[l1] > b[l2])
      ans += 200, l1++, l2++;
    else if (a[l1] < b[r2])
      ans -= 200, l1++, r2--;
    else
      l1++, r2--;
  printf("%d\n", ans);
  return 0;
}