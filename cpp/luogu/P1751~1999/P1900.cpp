#include <cstdio>
bool a[1900010];
int n, q[977790], ans;
int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    int sum = i, j = i;
    while (j) sum += j % 10, j /= 10;
    if (sum <= n) a[sum] = 1;
  }
  for (int i = 1; i <= n; ++i)
    if (a[i] == 0) q[++ans] = i;
  printf("%d\n", ans);
  int t, p;
  scanf("%d", &t);
  while (t--) {
    scanf("%d", &p);
    printf("%d ", q[p]);
  }
}