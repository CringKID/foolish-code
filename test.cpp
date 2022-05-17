#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
const int kMaxN = 1e3 + 5;

vector <int> ed[kMaxN];
int n, m, e, ans, vis[kMaxN], match[kMaxN];
bool DFS (int x, int cur) {
  if (vis[x] == cur) {
    return false;
  }
  vis[x] = cur;
  for (int to : ed[x]) {
    if (!match[to] || DFS (match[to], cur)) {
      match[to] = x;
      return true;
    }
  }
  return false;
}
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n >> m >> e;
  for (int i = 1, from, to; i <= e; i++) {
    cin >> from >> to, ed[from].push_back (to);
  }
  for (int i = 1; i <= n; i++) {
    ans += DFS (i, i);
  }
  cout << ans << '\n';
  return 0;
}