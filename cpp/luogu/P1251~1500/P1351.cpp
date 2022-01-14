#include <bits/stdc++.h>

using namespace std;

const int maxn = 2e5 + 5, mod = 1e4 + 7;

struct road {
  int to, next;
} edge[maxn << 1];

int cnt, head[maxn], val[maxn], n, ans, mmax;

inline void add(int from, int to) { edge[++cnt] = (road){to, head[from]}, head[from] = cnt; }

int main() {
  scanf("%d", &n);
  for (register int i = 1, from, to; i < n; i++) scanf("%d %d", &from, &to), add(from, to), add(to, from);
  for (register int i = 1; i <= n; i++) scanf("%d", &val[i]);

  for (register int i = 1, max1, max2, t1, t2; i <= n; i++) {
    max1 = 0, max2 = 0, t1 = 0, t2 = 0;

    for (register int j = head[i]; j; j = edge[j].next) {
      if (val[edge[j].to] > max1)
        max2 = max1, max1 = val[edge[j].to];
      else if (val[edge[j].to] > max2)
        max2 = val[edge[j].to];

      cerr << "*******" << endl;

      t1 = (t1 + val[edge[j].to]) % mod, t2 = (t2 + val[edge[j].to] * val[edge[j].to] % mod) % mod;
    }

    t1 = t1 * t1 % mod, ans = (ans + t1 + mod - t2) % mod, mmax = max(mmax, max1 * max2);
  }

  return printf("%d %d\n", mmax, ans) & 0;
}