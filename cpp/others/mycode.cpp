#include <bits/stdc++.h>
using namespace std;
namespace gengyf {
#define ll long long
const int maxn = 1e6 + 10;
inline ll read() {
  ll x = 0, f = 1;
  char c = getchar();
  while (c < '0' || c > '9') {
    if (c == '-') f = -1;
    c = getchar();
  }
  while (c >= '0' && c <= '9') {
    x = (x * 10) + c - '0';
    c = getchar();
  }
  return x * f;
}
ll n, k, m, a[maxn], t[maxn];
int f[maxn][2], g[maxn];
int main() {
  n = read();
  k = read();
  m = read();
  for (int i = 1; i <= n; i++) {
    a[i] = read();
  }
  ll l = 1, r = k + 1, lim = log2(m) + 1;
  for (int i = 1; i <= n; i++) {
    while (r < n && a[r + 1] - a[i] < a[i] - a[l]) {
      l++, r++;
    }
    f[i][0] = (a[r] - a[i] > a[i] - a[l] ? r : l);
  }
  if (m & 1) {
    for (int i = 1; i <= n; i++) {
      g[i] = f[i][0];
    }
  } else {
    for (int i = 1; i <= n; i++) {
      g[i] = i;
    }
  }
  r = 1;
  t[0] = 1;
  for (int i = 1; i <= lim; i++) t[i] = t[i - 1] << 1;
  for (int j = 1; j <= lim; j++) {
    for (int i = 1; i <= n; i++) {
      f[i][r] = f[f[i][r ^ 1]][r ^ 1];
    }
    if (m & t[j]) {
      for (int i = 1; i <= n; i++) {
        g[i] = f[g[i]][r];
      }
    }
    r ^= 1;
  }
  for (int i = 1; i <= n; i++) {
    printf("%d ", g[i]);
  }
  return 0;
}
}  // namespace gengyf
signed main() {
  gengyf::main();
  return 0;
}