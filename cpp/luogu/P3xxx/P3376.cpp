#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
const int kMaxN = 1e4 + 5;
using ll = long long;

int n, m, s, t, depth[kMaxN], que[kMaxN], l, r;
ll ans, tot = 1, head[kMaxN];
struct Edge {
  ll to, next, val;
} edge[kMaxN * 20];
void add (int from, int to, int dis) {
  edge[++tot] = {to, head[from], dis};
  head[from] = tot;
}
bool BFS () {
  fill (depth, depth + n + 1, 0);
  que[l = r = 1] = s, depth[s] = 1;
  while (l <= r) {
    int from = que[l++];
    for (int i = head[from], to; i; i = edge[i].next) {
      to = edge[i].to;
      if (edge[i].val && !depth[to]) {
        depth[to] = depth[from] + 1;
        que[++r] = to;
      }
    }
  }
  return depth[t];
}
ll DFS (int from, ll sum) {
  if (from == t) {
    return sum;
  }
  ll ans = 0;
  for (int i = head[from], to; i && sum; i = edge[i].next) {
    to = edge[i].to;
    if (edge[i].val && depth[to] == depth[from] + 1) {
      ll rec = DFS (to, min (edge[i].val, sum));
      edge[i].val -= rec, edge[i ^ 1].val += rec;
      sum -= rec, ans += rec;
    }
  }
  if (!ans) {
    depth[from] = 0;
  }
  return ans;
}

int main() {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n >> m >> s >> t;
  for (int i = 1, from, to; i <= m; i++) {
    ll dis;
    cin >> from >> to >> dis;
    add (from, to, dis), add (to, from, 0);
  }
  while (BFS ()) {
    ans += DFS (s, 1e18);
  }
  cout << ans << '\n';
  return 0;
}