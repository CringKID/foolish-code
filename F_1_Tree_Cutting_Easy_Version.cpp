#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
using Pii = pair <int, int>;
const int kMaxN = 3e5 + 5;

vector <int> ve[kMaxN];
int val1, val2, arr1[kMaxN], arr2[kMaxN], col[kMaxN], ans, n;
void DFS (int x, int cur = 0) {
  arr1[x] = col[x] == 1, arr2[x] = col[x] == 2;
  for (int to : ve[x]) {
    if (to == cur) {
      continue;
    }
    DFS (to, x);
    arr1[x] += arr1[to], arr2[x] += arr2[to];
  }
  if (1ll * arr1[x] * arr2[x] == 0 && (arr1[x] == val1 || arr2[x] == val2)) {
    ans++;
  }
}
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> col[i];
    col[i] == 1 && (val1++);
    col[i] == 2 && (val2++);
  }
  for (int i = 1, from, to; i < n; i++) {
    cin >> from >> to;
    ve[from].push_back (to);
    ve[to].push_back (from);
  }
  DFS (1);
  cout << ans << '\n';
  return 0;
}