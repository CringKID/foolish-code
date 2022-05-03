#include <iostream>
#include <algorithm>
#include <numeric>

using namespace std;
using ll = long long;
const int kMaxN = 2e5 + 5;

struct Query {
  int idx, val;
  ll ans;
} que[kMaxN];
struct Edge {
  int from, to, val;
} edge[kMaxN];
int n, m, fath[kMaxN], siz[kMaxN];
int root (int x) {
  return fath[x] == x ? x : fath[x] = root (fath[x]);
}
void Union (int x, int y) {
  x = root (x), y = root (y);
  fath[x] = y, siz[x] += siz[y];
  siz[y] = siz[x];
}
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n >> m;
  for_each (edge + 1, edge + n, [] (Edge &ed) { cin >> ed.from >> ed.to >> ed.val; });
  for (int i = 0; i < m; i++) {
    cin >> que[i].val, que[i].idx = i, que[i].ans = 0;
  }
  sort (edge + 1, edge + n, [] (Edge e1, Edge e2) { return e1.val < e2.val; });
  sort (que, que + m, [] (Query q1, Query q2) { return q1.val < q2.val; });
  iota (fath + 1, fath + n + 1, 1), fill (siz + 1, siz + n + 1, 1);
  for (int i = 0, j = 1; i < m; i++) {
    que[i].ans = que[i - 1].ans;
    for ( ; j < n && edge[j].val <= que[i].val; j++) {
      int from = edge[j].from, to = edge[j].to;
      que[i].ans += 1ll * siz[root (from)] * siz[root (to)];
      Union (from, to);
    }
  }
  sort (que, que + m, [] (Query q1, Query q2) { return q1.idx < q2.idx; });
  for_each (que, que + m, [] (Query q) { cout << q.ans << ' '; });
  return 0;
}