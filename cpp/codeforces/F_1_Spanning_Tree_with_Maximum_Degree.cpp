#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;
const int kMaxN = 2e5 + 5;

int deg[kMaxN];
vector <int> ve[kMaxN];
struct UFS {
  int fath[kMaxN];
  void init (int n = kMaxN) {
    memset (fath, -1, sizeof (int) * n);
  }
  int size (int x) {
    return -fath[find (x)];
  }
  int find (int x) {
    int save = x;
    for ( ; fath[save] >= 0; save = fath[save]) {
    }
    while (x != save) {
      int tmp = fath[x];
      fath[x] = save, x = tmp;
    }
    return save;
  }
  void Union (int x, int y) {
    int fx = find (x), fy = find (y);
    if (fath[fx] > fath[fy]) {
      swap (fx, fy);
    }
    fath[fx] += fath[fy], fath[fy] = fx;
  }
} ufs;
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  int n, m; cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    int from, to; cin >> from >> to;
    ve[from].push_back (to);
    ve[to].push_back (from);
    deg[from]++, deg[to]++;
  }
  int x = 1;
  for (int i = 1; i <= n; i++) {
    if (deg[x] < deg[i]) {
      x = i;
    }
  }
  ufs.init ();
  for (int to : ve[x]) {
    ufs.Union (x, to);
    cout << x << ' ' << to << '\n';
  }
  for (int i = 1; i <= n; i++) {
    for (int to : ve[i]) {
      if (ufs.find (i) != ufs.find (to)) {
        cout << i << ' ' << to << '\n';
        ufs.Union (i, to);
      }
    }
  }
  return 0;
}