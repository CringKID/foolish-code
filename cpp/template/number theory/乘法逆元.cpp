#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 3e6 + 5;
int tmp[maxn], n, mod;
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
  return flag ? X : ~(X - 1);
}
int main() {
  n = read(), mod = read();
  tmp[1] = 1;
  puts("1");
  for (int i = 2; i <= n; i++) {
    tmp[i] = (ll)(mod - mod / i) * tmp[mod % i] % mod;
    printf("%d\n", tmp[i]);
  }
  return 0;
}