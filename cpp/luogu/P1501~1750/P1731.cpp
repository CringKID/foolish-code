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
    X = (X << 1) + (X << 3) + ch - '0';
    ch = getchar();
  }
  if (flag) return X;
  return ~(X - 1);
}
void write(int X) {
  if (X < 0) {
    X = ~(X - 1);
    putchar('-');
  }
  if (X > 9) write(X / 10);
  putchar(X % 10 + '0');
}
const int maxn = 25;
int r[maxn], h[maxn], minn = 2e9, n, m;
void dfs(int x, int y, int k, int z) {
  if (y < 0 || x > m + 1) return;
  if (k >= minn) return;
  if (y == 0 && x == m + 1) {
    k += r[1] * r[1];
    minn = min(minn, k);
    return;
  }
  if (k + z + r[1] * r[1] > minn) return;
  if (y - (r[x - 1]) * (r[x - 1]) * (h[x - 1]) * z > 0) return;
  for (int i = r[x - 1] - 1; i >= z; i--)
    for (int j = h[x - 1] - 1; j >= z; j--)
      if (y - i * i * j >= 0 && x + 1 <= m + 1) {
        r[x] = i;
        h[x] = j;
        dfs(x + 1, y - i * i * j, k + (i * 2 * j), z - 1);
        h[x] = 0;
        r[x] = 0;
      }
  return;
}
int main() {
  n = read(), m = read();
  r[0] = h[0] = (int)sqrt(n);
  dfs(1, n, 0, m);
  if (minn == 2147483647)
    write(0);
  else
    write(minn);
  return 0;
}