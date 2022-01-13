#include <bits/stdc++.h>
using namespace std;
inline int read() {
  int X = 0;
  bool flag = 1;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    if (ch == '-') flag = 0;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    X = (X << 3) + (X << 1) + ch - '0';
    ch = getchar();
  }
  return flag ? X : ~(X - 1);
}
const int maxn = 1e6 + 10;
int mmax[maxn][21], l, r, n, m;
int query(int l, int r) {
  int x = log2(r - l + 1);
  return max(mmax[l][x], mmax[r - (1 << x) + 1][x]);
}
int main() {
  n = read(), m = read();
  for (register int i = 1; i <= n; i++) mmax[i][0] = read();
  for (register int i = 1; i <= 21; i++)
    for (register int j = 1; j + (1 << i) - 1 <= n; j++)
      mmax[j][i] = max(mmax[j][i - 1], mmax[j + (1 << (i - 1))][i - 1]);
  for (register int i = 1; i <= m; i++) {
    l = read(), r = read();
    printf("%d\n", query(l, r));
  }
  return 0;
}