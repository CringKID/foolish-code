#include <bits/stdc++.h>
using namespace std;
int n;
double l, r, a[25];
double f(double x) {
  double u = 1, p = 0;
  for (int i = n; i >= 0; --i) {
    p += u * a[i];
    u *= x;
  }
  return p;
}
double triple(double l, double r) {
  while (l + (1e-7) < r) {
    double lmid = l + (r - l) / 3, rmid = r - (r - l) / 3;
    if (f(lmid) <= f(rmid))
      l = lmid;
    else
      r = rmid;
  }
  return r;
}
int main() {
  scanf("%d", &n);
  scanf("%lf %lf", &l, &r);
  for (int i = 0; i <= n; i++) scanf("%lf", &a[i]);
  printf("%.5lf", triple(l, r));
  return 0;
}