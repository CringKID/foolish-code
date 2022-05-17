#include <iostream>
#include <vector>

using namespace std;
const int kMaxN = 1e3 + 5;

vector <int> ed[kMaxN];
int n, m, t, match[kMaxN], vis[kMaxN], ans;
bool DFS (int x, int cur) {
  if (vis[x] == cur) {
    return false;
  }
  vis[x] = cur;
  for (int v : ed[x]) {
    if ((match[v] == 0) || DFS (match[v], cur)) {
      match[v] = x;
      return true;
    }
  }
  return false;
}
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n >> m >> t;
  for (int u, v; t; t--) {
    cin >> u >> v;
    ed[u].push_back(v);
  }
  for (int i = 1; i <= n; i++) {
    DFS (i, i) ? ans++ : 0;
  }
  cout << ans << '\n';
  return 0;
}