#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e7 + 5;

int n, a[maxn], s[maxn], tl[maxn], tr[maxn];
long long l, r;
inline int read() {
  register int X = 0;
  register bool flag = 1;
  register char ch = getchar();
  while ((ch < '0' || ch > '9') && ch != '-') ch = getchar();
  if (ch == '-') flag = 0, ch = getchar();
  while (ch >= '0' && ch <= '9') X = (X << 1) + (X << 3) + (ch ^ 48), ch = getchar();
  return flag ? X : ~(X - 1);
}

int main() {
  n = read();

  for (register int i = 1, res = 0, top = 0; i <= n; ++i) {
    a[i] = read(), res = top;
    while (res && a[s[res]] > a[i]) --res;

    if (res) tr[s[res]] = i;
    if (res < top) tl[i] = s[res + 1];

    s[top = ++res] = i;
  }

  for (register int i = 1; i <= n; ++i) l ^= 1ll * i * (tl[i] + 1), r ^= 1ll * i * (tr[i] + 1);

  return printf("%lld %lld\n", l, r) & 0;
}