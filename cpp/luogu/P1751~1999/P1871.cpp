#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e4 + 5, maxm = 1e5 + 5;
int p[maxn], q[maxm], k[maxn], n, m, a, x, t = 0;
bool b[maxm];
char s[2];
int main() {
  scanf("%d %d", &n, &m);
  for (register int i = 2; i <= n; i++) {
    if (!b[i]) p[++t] = i, q[i] = t;
    for (register int j = 1; j <= t && p[j] * i <= n; j++) {
      a = p[j] * i;
      b[a] = 1, q[a] = j;
      if (!i % p[j]) break;
    }
  }
  memset(b, 0, sizeof(b));
  while (m--) {
    scanf(" %s%d", s, &a);
    x = a;
    if (s[0] == 43) {
      if (b[a]) {
        puts("Already on");
        continue;
      }
      while (x > 1) {
        if (k[q[x]]) break;
        x /= p[q[x]];
      }
      if (x != 1) {
        printf("Conflict with %d\n", k[q[x]]);
        continue;
      }
      b[x = a] = 1;
      puts("Success");
      while (x > 1) {
        k[q[x]] = a;
        x /= p[q[x]];
      }
    } else {
      if (!b[a]) {
        puts("Already off");
        continue;
      }
      b[a] = 0;
      puts("Success");
      while (x > 1) {
        k[q[x]] = 0;
        x /= p[q[x]];
      }
    }
  }
  return 0;
}