#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
using Pii = pair <int, int>;
const int kMaxN = 1e3 + 5;

vector <Pii> ve;
vector <int> edge[kMaxN];
int save, n, m, from, to, fath[kMaxN], dist[kMaxN];
void DFS (int x, int fa, int dep) {
  if (dep >= dist[save]) {
    save = x;
  }
  dist[x] = dep, fath[x] = fa;
  for (int to : edge[x]) {
    if (to != fa) {
      DFS (to, x, dep + 1);
    }
  }
}
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n >> m;
  for (int i = 0; i < m; i++) {
    cin >> from >> to;
    edge[from].push_back (to);
    edge[to].push_back (from);
  }
  for (int i = 1; i <= n; i++) {
    if (!fath[i]) {
      save = 0;
      DFS (i, i, 0);
      int sa = save;
      save = 0;
      DFS (sa, sa, 0);
      sa = save;
      int dsa = dist[sa], hdsa = dist[sa] / 2;
      for (int j = 0; j < hdsa; j++) {
        sa = fath[sa];
      }
      ve.emplace_back (dsa, sa);
    }
  }
  sort (ve.begin (), ve.end ());
  if (ve.size () == 1) {
    cout << dist[save] << '\n';
    return 0;
  }
  int x = ve.size () - 1, lena = ve[x].first, lenb = ve[x - 1].first, len = max (lena, max (lena - lena / 2, lena / 2) + 1 + max (lenb - lenb / 2, lenb / 2));
  if (ve.size () > 2) {
    len = max (lena, max (ve[x - 2].first / 2, ve[x - 2].first - ve[x - 2].first / 2) + 2 + max (lenb - lenb / 2, lenb / 2));
  }
  for (int i = 0; i < x; i++) {
    edge[ve[x].second].push_back (ve[i].second);
    edge[ve[i].second].push_back (ve[x].second);
  }
  save = 0;
  DFS (1, 0, 0);
  int sa = save;
  save = 0;
  DFS (sa, 0, 0);
  len = dist[save];
  cout << len << '\n';
  for (int i = 0; i < x; i++) {
    cout << ve[x].second << ' ' << ve[i].second << '\n';
  }
  return 0;
}