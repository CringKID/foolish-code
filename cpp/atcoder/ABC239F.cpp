#include <iostream>
#include <algorithm>
#include <atcoder/all>
#include <vector>

using namespace std;
using namespace atcoder;
using Pii = pair <int, int>;
const int kMaxN = 2e5 + 5;

dsu DSU;
bool merge (int a, int b) {
  bool flag = DSU.same (a, b);
  DSU.merge (a, b);
  return flag;
}
int n, m, d[kMaxN];
vector <int> ve1;
vector <Pii> res;
vector <vector <int> > cur (kMaxN), ve2;
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n >> m, DSU = dsu (n + 1);
  for_each (d + 1, d + n + 1, [](int &x) { cin >> x; });
  for (int from, to; m; m--) {
    cin >> from >> to, d[from]--, d[to]--;
    if (d[from] < 0 || d[to] < 0 || merge (from, to)) {
      cout << -1 << '\n';
      return 0;
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < d[i]; j++) {
      cur[DSU.leader (i)].push_back (i);
    }
  }
  for (int i = 1; i <= n; i++) {
    cur[i].size () == 1 ? ve1.push_back (cur[i].back ()) : void ();
    cur[i].size () > 1 ? ve2.push_back (cur[i]) : void ();
  }
  for (vector <int> ve : ve2) {
    for (int i = 0; i < ve.size () - 1; i++) {
      if (ve1.empty ()) {
        cout << -1 << '\n';
        return 0;
      }
      merge (ve1.back (), ve[i]), res.push_back ({ve1.back (), ve[i]}), ve1.pop_back ();
    }
    ve1.push_back (ve.back ());
  }
  if (ve1.size () == 2) {
    if (merge (ve1[0], ve1[1])) {
      cout << -1 << '\n';
      return 0;
    }
    res.push_back ({ve1[0], ve1[1]});
  } else {
    cout << -1 << '\n';
    return 0;
  }
  if (DSU.size (DSU.leader (1)) != n) {
    cout << -1 << '\n';
    return 0;
  }
  for (Pii P : res) {
    cout << P.first << ' ' << P.second << '\n';
  }
  return 0;
}