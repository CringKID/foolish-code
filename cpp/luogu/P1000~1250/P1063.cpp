#include <bits/stdc++.h>
using namespace std;
inline int max(int a, int b) {
  return (b & ((a - b) >> 31) | a & (~(a - b) >> 31));
}
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
const int maxn2 = 305;
int n, a[maxn2], dp[maxn2][maxn2], mmax = -1;
int main() {
  n = read();
  for (int i = 1; i <= n; i++) a[i] = a[i + n] = read();
  for (int i = 2; i < n * 2; i++)
    for (int j = i - 1; i - j < n && j >= 1; j--) {
      for (int k = j; k < i; k++) dp[j][i] = max(dp[j][i], dp[j][k] + dp[k + 1][i] + a[j] * a[k + 1] * a[i + 1]);
      mmax = max(mmax, dp[j][i]);
    }
  printf("%d\n", mmax);
  return 0;
}