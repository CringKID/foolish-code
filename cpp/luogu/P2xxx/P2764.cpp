#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;
const int kMaxN = 305, kMaxM = 1.2e4 + 5;

int n, m, tot, ans, head[kMaxN], cur[kMaxN];
bool vis[kMaxN];
struct Edge {
  int to, next;
} edge[kMaxM];
void add (int from, int to) {
  edge[++tot] = {to, head[from]};
  head[from] = tot;
}
bool DFS (int now) {
  for (int i = head[now], to; i; i = edge[i].next) {
    to = edge[i].to;
    if (!vis[to]) {
      vis[to] = true;
      if (!cur[to] || DFS (cur[to])) {
        cur[now] = to;
        cur[to] = now;
        return true;
      }
    }
  }
  return false;
}
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);
  cin >> n >> m, ans = n;
  for (int i = 1, from, to; i <= m; i++) {
    cin >> from >> to;
    add (from, to + n);
  }
  for (int i = 1; i <= n; i++) {
    if (!cur[i]) {
      fill (vis, vis + n * 2 + 1, false); 
      ans -= DFS (i);
    }
  }
  fill (vis, vis + n * 2 + 1, false);
  for (int i = 1, k; i <= n; i++) {
    if (!vis[i]) {
      k = i + n;
      do {
        k -= n;
        cout << k << ' ';
      } while (vis[k] = true, k = cur[k]);
      cout << '\n';
    }
  }
  cout << ans << '\n';
  return 0;
}