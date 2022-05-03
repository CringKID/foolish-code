#include <iostream>
#include <algorithm>

using namespace std;
using Pii = pair <int, int>;
const int kMaxN = 2e5 + 5;

Pii edge[kMaxN << 1];
int n, head[kMaxN], cnt, tot = 1, l[kMaxN], r[kMaxN];
void DFS (int x, int fa) {
  l[x] = cnt + 1;
  bool flag = true;
  for (int i = head[x]; i; i = edge[i].second) {
    edge[i].first != fa ? (DFS (edge[i].first, x), flag = 0) : 0;
  }
  (flag ? ++cnt : 0), r[x] = cnt;
}
int main () {
  ios :: sync_with_stdio (0);
  cin.tie (0), cin.tie (0);

  cin >> n;
  for (int i = 1, from, to; i < n; ++i) {
    cin >> from >> to;
    edge[++tot] = {to, head[from]}, head[from] = tot;
    edge[++tot] = {from, head[to]}, head[to] = tot;
  }
  DFS (1, 0);
  for (int i = 1; i <= n; i++) {
    cout << l[i] << " " << r[i] << '\n';
  }
  return 0;
}