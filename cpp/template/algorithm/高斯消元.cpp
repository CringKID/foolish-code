#include <bits/stdc++.h>

using namespace std;

const int maxn = 105;

double mmap[maxn][maxn], Ans[maxn];
int n;

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n + 1; j++) scanf("%lf", &mmap[i][j]);

  for (int i = 1, mmax; i <= n; i++) {
    mmax = i;
    for (int j = i + 1; j <= n; j++)
      if (fabs(mmap[mmax][i]) < fabs(mmap[j][i])) mmax = j;

    if (fabs(mmap[mmax][i]) < 1e-7) return puts("No Solution"), 0;
    if (i != mmax) swap(mmap[i], mmap[mmax]);

    double reg = mmap[i][i];
    for (int j = i; j <= n + 1; j++) mmap[i][j] /= reg;

    for (int j = i + 1; j <= n; j++) {
      reg = mmap[j][i];
      for (int k = i; k <= n + 1; k++) mmap[j][k] -= mmap[i][k] * reg;
    }
  }

  Ans[n] = mmap[n][n + 1];

  for (int i = n - 1; i >= 1; i--) {
    Ans[i] = mmap[i][n + 1];
    for (int j = i + 1; j <= n; j++) Ans[i] -= (mmap[i][j] * Ans[j]);
  }

  for (int i = 1; i <= n; i++) printf("%.2lf\n", Ans[i]);

  return 0;
}