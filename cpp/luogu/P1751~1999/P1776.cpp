#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 5;
int n, m, V, W, M, cnt, dp[maxn], v[maxn], w[maxn];
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
    putchar('-');
    X = ~(X - 1);
  }
  if (X > 9) write(X / 10);
  putchar(X % 10 + '0');
}
inline int max(int a, int b) {
  return (b & ((a - b) >> 31) | a & (~(a - b) >> 31));
}
int main() {
  n = read(), m = read();
  for (int i = 1; i <= n; i++) {
    V = read(), W = read(), M = read();
    for (int j = 1; j <= M; j *= 2) {
      v[++cnt] = V * j;
      w[cnt] = W * j;
      M -= j;
    }
    if (M > 0) {
      v[++cnt] = V * M;
      w[cnt] = W * M;
    }
  }
  for (int i = 1; i <= cnt; i++)
    for (int j = m; j >= w[i]; j--)
      dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
  write(dp[m]);
  return 0;
}