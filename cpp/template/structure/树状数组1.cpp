#include <bits/stdc++.h>
using namespace std;
int n, m, tree[500005];
int lowbit(int x) {
  return x & -x;
}
void gx(int x, int y) {
  while (x <= n) {
    tree[x] += y;
    x += lowbit(x);
  }
  return;
}
int cx(int x) {
  int cnt = 0;
  while (x > 0) {
    cnt += tree[x];
    x -= lowbit(x);
  }
  return cnt;
}
int main() {
  scanf("%d %d", &n, &m);
  for (int i = 1; i <= n; i++) {
    int temp;
    scanf("%d", &temp);
    gx(i, temp);
  }
  for (int i = 0; i < m; i++) {
    int temp, x, k;
    scanf("%d %d %d", &temp, &x, &k);
    if (temp == 1)
      gx(x, k);
    else
      printf("%d\n", cx(k) - cx(x - 1));
  }
  return 0;
}