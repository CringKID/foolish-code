#include <bits/stdc++.h>

using namespace std;

const int maxn = 5e3 + 5;

int n;
double x[maxn], y[maxn], a[maxn], b[maxn], ans;

inline bool checknum(register double x) {
  register double l = -2e9, r = 2e9;

  for (register int i = 2; i <= n; i++)
    if (a[i] < 0)
      l = max(l, (x - b[i]) / a[i]);
    else if (a[i] > 0)
      r = min(r, (x - b[i]) / a[i]);
    else if (x < b[i])
      return false;

  return l <= r;
}

int main() {
  scanf("%d %lf %lf", &n, &x[1], &y[1]);
  for (register int i = 2; i <= n; i++) scanf("%lf %lf", &x[i], &y[i]), a[i] = (y[i] - y[i - 1]) / (x[i] - x[i - 1]), b[i] = y[i] - a[i] * x[i];

  register double mid, l = 0, r = 1000000;
  while (l <= r) {
    mid = (l + r) / 2;
    if (checknum(mid))
      r = mid - 0.0001, ans = mid;
    else
      l = mid + 0.0001;
  }

  return printf("%.2lf\n", ans) & 0;
}