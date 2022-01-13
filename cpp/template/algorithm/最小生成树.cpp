#include <bits/stdc++.h>
using namespace std;
int n, m, father[5005], ans, cnt;
struct road {
  int from, to, len;
} r[200005];
bool cmp(road a, road b) {
  return a.len < b.len;
}
int root(int x) {
  if (x != father[x]) father[x] = root(father[x]);
  return x = father[x];
}
int main() {
  scanf("%d %d", &n, &m);
  for (int i = 0; i < m; i++) scanf("%d %d %d", &r[i].from, &r[i].to, &r[i].len);
  sort(r, r + m, cmp);
  for (int i = 1; i <= n; i++) father[i] = i;
  for (int i = 0; i < m; i++) {
    int r1 = root(r[i].from), r2 = root(r[i].to);
    if (r1 != r2) {
      ans += r[i].len;
      father[r1] = r2;
      cnt++;
      if (cnt == n - 1) {
        printf("%d\n", ans);
        return 0;
      }
    }
  }
  printf("orz");
  return 0;
}