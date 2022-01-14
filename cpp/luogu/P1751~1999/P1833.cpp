#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e4 + 5;
int h1, m1, h2, m2, n, T, t[maxn], c[maxn], p[maxn], dp[maxn];
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
int main() {
  h1 = read(), m1 = read(), h2 = read(), m2 = read(), n = read();
  T = (h2 - h1) * 60 + (m2 - m1);
  for (int i = 1; i <= n; i++) t[i] = read(), c[i] = read(), p[i] = read();
  for (int i = 1; i <= n; i++)
    if (!p[i])
      for (int j = t[i]; j <= T; j++) dp[j] = max(dp[j], dp[j - t[i]] + c[i]);
    else if (p[i] == 1)
      for (int j = T; j >= t[i]; j--) dp[j] = max(dp[j], dp[j - t[i]] + c[i]);
    else
      for (int j = T; j >= 0; j--)
        for (int k = 1; k <= p[i] && j >= k * t[i]; k++) dp[j] = max(dp[j], dp[j - t[i] * k] + c[i] * k);
  printf("%d\n", dp[T]);
  return 0;
}