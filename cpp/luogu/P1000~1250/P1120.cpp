#include <bits/stdc++.h>
using namespace std;
int n, cnt, tot, mmax, mmin, tmp[75];
void dfs(int depth, int sum, int now, int p, int qb) {
  if (!depth) {
    printf("%d\n", now);
    exit(0);
  }
  while (!tmp[qb]) --qb;
  p = min(p, qb);
  if (sum == now) {
    dfs(depth - 1, 0, now, qb, qb);
    return;
  }
  for (register int i = min(p, now - sum); i >= mmin; i--)
    if (tmp[i] && i + sum <= now) {
      tmp[i]--;
      dfs(depth, sum + i, now, i, qb);
      tmp[i]++;
      if (!sum || sum + i == now) break;
    }
}
int main() {
  scanf("%d", &n);
  mmin = 70;
  while (n--) {
    int t;
    scanf("%d", &t);
    if (t <= 50) {
      cnt++, tmp[t]++, tot += t;
      mmax = max(mmax, t), mmin = min(mmin, t);
    }
  }
  int t = (tot >> 1);
  for (register int i = mmax; i <= t; i++)
    if (!(tot % i)) dfs(tot / i, 0, i, mmax, mmax);
  printf("%d\n", tot);
  return 0;
}