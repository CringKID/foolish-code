#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 5, bit = 16, base = 256;
int n, a[maxn], cnt[base], b[maxn];
inline int calc(int x, int d) { return (x >> (d * bit)) & (base - 1); }
inline void radix_sort() {
  int *x = a, *y = b;
  for (register int i = 0; i < 2; i++) {
    for (register int j = 0; j < base; j++) cnt[j] = 0;
    for (register int j = 0; j < n; j++) cnt[calc(x[j], i)]++;
    for (register int j = 1; j < base; j++) cnt[j] += cnt[j - 1];
    for (register int j = n - 1; j >= 0; j--) y[--cnt[calc(x[j], i)]] = x[j];
    swap(x, y);
  }
  for (register int i = 0; i < n; i++) printf("%d ", x[i]);
}
int main() {
  scanf("%d", &n);
  for (register int i = 0; i < n; i++) scanf("%d", &a[i]);
  radix_sort();
  return 0;
}