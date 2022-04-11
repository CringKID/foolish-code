#include <iostream>
#include <algorithm>
#include <set>

using namespace std;
const int kMaxN = 2e5 + 5;

set <int, greater <int> > Set;
int n, k, cnt, x, arr[kMaxN], lfath[kMaxN], rfath[kMaxN], Map[kMaxN], ans[kMaxN];
int lroot (int x) {
  return lfath[x] == x ? x : lfath[x] = lroot (lfath[x]);
}
int rroot (int x) {
  return rfath[x] == x ? x : rfath[x] = rroot (rfath[x]);
}
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n >> k;
  for (int i = 1; i <= n; i++) {
    cin >> arr[i];
    Set.insert (arr[i]);
    Map[arr[i]] = i;
  }
  for (int i = 0; i <= n + 1; i++) {
    lfath[i] = i, rfath[i] = i;
  }
  while (cnt <= n) {
    int tmp, pos, cur1, cur2, tot1 = 0, tot2 = 0;
    x++, tmp = *Set.begin (), pos = Map[tmp], cur1 = rroot (pos + 1), cur2 = lroot (pos - 1), cnt++;
    lfath[pos] = lroot (pos - 1), rfath[pos] = rroot (pos + 1);
    Set.erase (tmp), ans[pos] = x % 2;
    while (tot1 < k && cur1 <= n) {
      tot1++, cnt++, ans[cur1] = x % 2;
      Set.erase (arr[cur1]), rfath[cur1] = rroot (cur1 + 1), lfath[cur1] = lroot (cur1 - 1);
      cur1 = rroot (pos);
    }
    while (tot2 < k && cur2 >= 1) {
      tot2++, cnt++, ans[cur2] = x % 2;
      Set.erase (arr[cur2]), rfath[rroot (cur2)] = rroot (cur2 + 1), lfath[cur2] = lroot (cur2 - 1);
      cur2 = lroot (pos);
    }
  }
  for (int i = 1; i <= n; i++) {
    cout << (!ans[i] ? 2 : ans[i]);
  }
  cout << '\n';
  return 0;
}