#include <iostream>
#include <algorithm>

using namespace std;
using Pii = pair <int, int>;
const int kMaxN = 2e5 + 5;

int n, k, r, tot, head[kMaxN], deg[kMaxN], ans[kMaxN];
Pii edge[kMaxN << 1];
void add (int from, int to) {
  edge[++tot] = make_pair (to, head[from]), head[from] = tot;
}
void solve (int x, int fath, int cur) {
  for (int i = head[x]; i; i = edge[i].second) {
    int to = edge[i].first;
    if (to == fath) {
      continue;
    }
    cur++, (cur > r ? cur = 1 : false);
    ans[i + 1 >> 1] = cur;
    solve (to, x, cur);
  }
}
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n >> k;
  for (int i = 1, x, y; i < n; i++) {
    cin >> x >> y;
    add (x, y), add (y, x);
    deg[x]++, deg[y]++;
  }
  sort (deg + 1, deg + n + 1);
  r = deg[n - k];
  solve (1, 0, 0);
  cout << r << '\n';
  for (int i = 1; i < n; i++) {
    cout << ans[i] << ' ';
  }
  return 0;
}