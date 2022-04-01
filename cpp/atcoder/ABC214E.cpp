#include <iostream>
#include <algorithm>
#include <set>

using namespace std;
using Pii = pair <int, int>;
const int kMaxN = 2e5 + 5, kMod = 1e9 + 7;

Pii pa[kMaxN];
int n, t, fix[kMaxN];
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> t;
  while (t--) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> pa[i].first >> pa[i].second;
    }
    bool tag = false;
    int cur = 0, rec = 0;
    sort (pa + 1, pa + n + 1);
    multiset <int> set1, set2;
    for (int i = 1; i <= n; i++) {
      if (!set2.size ()) {
        cur = pa[rec + 1].first;
      }
      for ( ; rec + 1 <= n && pa[rec + 1].first <= cur; set2.insert (pa[++rec].second)) {
      }
      int x = *set2.begin ();
      set2.erase (set2.find (x));
      if (x < cur) {
        tag = 1;
      }
      cur++;
    }
    cout << (tag ? "No" : "Yes") << '\n';
  }
  return 0;
}