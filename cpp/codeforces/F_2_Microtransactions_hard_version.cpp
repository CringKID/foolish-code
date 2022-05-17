#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
using ll = long long;
using Pii = pair <int, int>;
using Pll = pair <ll, ll>;
const int kMaxN = 2e5 + 5, kMod = 998244353, kInf = 1e9;

vector <int> edge[kMaxN];
int arr[kMaxN * 10], sum, cur[kMaxN], n, m;
bool check (int x) {
  fill (arr + 1, arr + x + 1, 0);
  for (int i = 1; i <= n; i++) {
    if (!edge[i].size ()) {
      continue;
    }
    int l = 0, r = int (edge[i].size ()) - 1;
    while (l != r) {
      int mid = (l + r) / 2;
      if (edge[i][mid + 1] <= x) {
        l = mid + 1;
      } else {
        r = mid;
      }
    }
    arr[edge[i][l]] += cur[i];
  }
  int money = 0, buy = 0;
  for (int i = 1; i <= x; i++) {
    money++;
    buy += min (money, arr[i]);
    money -= min (money, arr[i]);
  }
  return money >= 2 * (sum - buy);
}
//#define contest
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);
#ifdef contest
  freopen (, , stdin);
  freopen (, , stdout);
#endif

  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> cur[i], sum += cur[i];
  }
  for (int i = 1, from, to; i <= m; i++) {
    cin >> from >> to;
    edge[to].push_back (from);
  }
  for (int i = 1; i <= n; i++) {
    sort (edge[i].begin (), edge[i].end ());
  }
  int l = sum, r = sum * 2;
  while (l != r) {
    int mid = l + r >> 1;
    if (check (mid)) {
      r = mid;
    } else {
      l = mid + 1;
    }
  }
  cout << l << '\n';
  return 0;
}