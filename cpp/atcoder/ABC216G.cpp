#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <set>

using namespace std;
const int kMaxN = 2e5 + 5;

int n, m, l[kMaxN], r[kMaxN], arr[kMaxN], cnt[kMaxN], dlt[kMaxN];
vector <int> vel[kMaxN], ver[kMaxN];
multiset <int> Set;
int main () {
  cin.tie(0), cout.tie (0);
  ios :: sync_with_stdio (false);

  cin >> n >> m;
  for (int i = 0; i < m; ++i) {
    cin >> l[i] >> r[i] >> arr[i];
    vel[l[i]].push_back(i);
    ver[r[i]].push_back(i);
  }
  memset (cnt, 0, sizeof (cnt)), memset (dlt, 0, sizeof (dlt));
  for (int i = 1; i <= n; i++) {
    for (auto j : vel[i]) {
      Set.insert (dlt[i - 1] + (r[j] - l[j] + 1) - arr[j]);
    }
    if (!Set.empty () && *Set.begin () == dlt[i - 1]) {
      dlt[i] = dlt[i - 1];
      cout << 1 << ' ';
    } else {
      dlt[i] = dlt[i - 1] + 1;
      cout << 0 << ' ';
    }
    for (int j : ver[i]) {
      Set.erase (Set.find (dlt[l[j] - 1] + (r[j] - l[j] + 1) - arr[j]));
    }
  }
  return 0;
}