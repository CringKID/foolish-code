#include <bits/stdc++.h>
using namespace std;
const int maxn = 1.1e7 + 5;
char a[maxn << 1];
int m[maxn << 1], cnt = 1, ans;
int main() {
  char ch = getchar();
  a[0] = '~', a[cnt] = '|';
  while (ch < 'a' || ch > 'z') ch = getchar();
  while (ch >= 'a' && ch <= 'z') a[++cnt] = ch, a[++cnt] = '|', ch = getchar();
  for (register int l = 1, r = 0, mid = 0; l <= cnt; l++) {
    if (l <= r) m[l] = min(m[(mid << 1) - l], r - l + 1);
    while (a[l - m[l]] == a[l + m[l]]) ++m[l];
    if (m[l] + l > r) r = m[l] + l - 1, mid = l;
    ans = max(ans, m[l]);
  }
  printf("%d\n", ans - 1);
  return 0;
}