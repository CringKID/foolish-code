#include <bits/stdc++.h>
using namespace std;
int i, j, k, n, m, s, ans, father[10005], a, b, c;
int root(int k) {
  if (father[k] == k) return k;
  return father[k] = root(father[k]);
}
int main() {
  cin >> n >> m;
  for (i = 1; i <= n; i++) father[i] = i;
  for (i = 1; i <= m; i++) {
    scanf("%d %d %d", &a, &b, &c);
    if (a == 1)
      father[root(b)] = root(c);
    else if (a == 2) {
      if (root(b) == root(c))
        printf("Y\n");
      else
        printf("N\n");
    }
  }
  return 0;
}