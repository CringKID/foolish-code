#include <bits/stdc++.h>

using namespace std;

const int maxn = 105;

int n, len, num;
char ch[maxn];

struct huge {
  int sum[maxn];
} d, p, q, r, s, t;

huge multi(huge x, huge y) {
  huge ans = d;

  for (register int i = 1; i <= n; i++)
    for (register int j = n - i + 1; j; j--) ans.sum[i + j - 1] += x.sum[i] * y.sum[j];
  for (register int i = 1; i < n; i++) ans.sum[i + 1] += ans.sum[i] / 10, ans.sum[i] %= 10;
  ans.sum[n] %= 10;

  return ans;
}

int main() {
  scanf("%s %d", ch, &n);
  len = strlen(ch);
  for (register int i = min(len, n); i; i--) p.sum[i] = ch[len - i] - '0';
  r = p, t.sum[len = 1] = 1;

  for (register int i = 1; i <= n; i++) {
    if (multi(p, r).sum[i] == p.sum[i]) continue;
    num = 1, s = r;

    do {
      r = multi(s, r);
      if ((++num) > 10) return puts("-1"), 0;
    } while (multi(p, r).sum[i] != p.sum[i]);

    for (register int j = 1; j <= len; j++) t.sum[j] *= num;
    for (register int j = 1; j < len; j++) t.sum[j + 1] += t.sum[j] / 10, t.sum[j] %= 10;
    if (t.sum[len] >= 10) t.sum[len + 1] += t.sum[len] / 10, t.sum[len++] %= 10;
  }

  for (register int i = len; i; i--) printf("%d", t.sum[i]);

  return 0;
}