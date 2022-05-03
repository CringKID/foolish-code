#include <iostream>
#include <algorithm>
#include <atcoder/all>
#include <vector>

using namespace std;
const int kMaxN = 1e5 + 5;

int n, q, arr[kMaxN];
vector <int> ve[kMaxN], ans[kMaxN];
void DFS (int x, int fa) {
  vector <int> cur; cur.push_back (arr[x]);
  for (int i : ve[x]) {
    if (i == fa) {
      continue;
    }
    DFS (i, x);
    for (int j : ans[i]) {
      cur.push_back (j);
    }
  }
  sort (cur.begin (), cur.end (), greater <int> ());
  int res = min (20, int (cur.size ()));
  for (int i = 0; i < res; i++) {
    ans[x].push_back (cur[i]);
  }
}
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n >> q;
  for_each (arr + 1, arr + n + 1, [] (int &x) { cin >> x; });
  for (int i = 1, from, to; i < n; i++) {
    cin >> from >> to;
    ve[from].push_back (to), ve[to].push_back (from);
  }
  DFS (1, -1);
  for (int x, y; q--; ) {
    cin >> x >> y;
    cout << ans[x][y - 1] << '\n';
  }
  return 0;
}