#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>

using namespace std;
using Pii = pair <int, int>;

int n, q;
priority_queue <Pii> que;
map <int, int> map1, map2;
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  for (cin >> q; q; q--) {
    cin >> n;
    for (int i = 0, x, val; i < n; i++) {
      cin >> x >> val;
      map1[x]++, map2[x] += val;
    }
    for (Pii P : map1) {
      que.push ({P.second, map2[P.first]});
    }
    int flag = -1, ans1 = 0, ans2 = 0;
    for ( ; !que.empty () && flag; ) {
      int sum = que.top ().first, cur = que.top ().second; que.pop ();
      (flag != sum ? ((flag = sum, ans1 += sum, ans2 += cur), 0) : ((sum == cur ? (sum--, cur--) : (sum--)), que.push ({sum, cur}), 0));
    }
    for ( ; !que.empty (); que.pop ()) {
    }
    map1.clear (), map2.clear ();
    cout << ans1 << ' ' << ans2 << '\n';
  }
  return 0;
}