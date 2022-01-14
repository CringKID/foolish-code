#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e3 + 5;
int a[maxn], sum[maxn], dpmin[maxn][maxn], dpmax[maxn][maxn], smi[maxn][maxn], n;
int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
    a[i + n] = a[i];
    sum[i] = sum[i - 1] + a[i];
    smi[i][i] = i;
  }
  for (int i = 1 + n; i <= (n << 1); i++) {
    sum[i] = sum[i - 1] + a[i];
    smi[i][i] = i;
  }
  for (int i = (n << 1) - 1; i; i--)
    for (int j = i + 1; j <= (n << 1); j++) {
      int jc = 0, tmp = 0x3f3f3f3f;
      dpmax[i][j] = max(dpmax[i][j - 1], dpmax[i + 1][j]) + sum[j] - sum[i - 1];
      for (int k = smi[i][j - 1]; k <= smi[i + 1][j]; k++) {
        int tt = dpmin[i][k] + dpmin[k + 1][j] + (sum[j] - sum[i - 1]);
        if (tt < tmp) {
          tmp = tt;
          jc = k;
        }
      }
      smi[i][j] = jc;
      dpmin[i][j] = tmp;
    }
  int mmax = 0, mmin = 0x3f3f3f3f;
  for (int i = 1; i <= n; i++) {
    mmax = max(mmax, dpmax[i][i + n - 1]);
    mmin = min(mmin, dpmin[i][i + n - 1]);
  }
  printf("%d\n%d\n", mmin, mmax);
  return 0;
}