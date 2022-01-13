#include <bits/stdc++.h>

#include <ext/pb_ds/priority_queue.hpp>
using namespace std;
int n, m, father[100001];
int find(int x) {
  if (father[x] == x) return x;
  return father[x] = find(father[x]);
}
int main() {
  scanf("%d %d", &n, &m);
  bool f[n + 1] = {0};
  for (int i = 1; i <= n; i++) father[i] = i;
  __gnu_pbds::priority_queue<pair<int, int>, greater<pair<int, int> > > q[n + 1];
  for (int i = 1; i <= n; i++) {
    int temp;
    scanf("%d", &temp);
    q[i].push(make_pair(temp, i));
  }
  for (int i = 1; i <= m; i++) {
    int k;
    scanf("%d", &k);
    if (k == 1) {
      int x, y;
      scanf("%d %d", &x, &y);
      int fx = find(x), fy = find(y);
      if (!(f[x] || f[y] || fx == fy)) {
        q[fx].join(q[fy]);
        father[fy] = fx;
      }
    } else {
      int x;
      scanf("%d", &x);
      if (!f[x]) {
        f[q[find(x)].top().second] = 1;
        printf("%d\n", q[find(x)].top().first);
        q[find(x)].pop();
      } else
        printf("-1\n");
    }
  }
  return 0;
}