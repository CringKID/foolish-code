#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;
using Pii = pair <int, int>;
using Pll = pair <ll, ll>;
const int kMaxN = 5e5 + 5, kMod = 1e9 + 7, kInf = 1e9;

int n, m, q, fath[kMaxN];
struct Edge {
  int from, to, val, idx;
  bool operator < (const Edge & e) const {
    return val < e.val;
  }
} edge[kMaxN];
string ans[kMaxN];
int root (int x) {
  return x == fath[x] ? x : fath[x] = root (fath[x]);
}
//#define contest
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);
#ifdef contest
  freopen (, , stdin);
  freopen (, , stdout);
#endif

  cin >> n >> m >> q;
  for (int i = 1; i <= n; i++) {
    fath[i] = i;
  }
  for (int i = 1; i <= m; i++) {
    cin >> edge[i].from >> edge[i].to >> edge[i].val;
    edge[i].idx = i;
  }
  for (int i = 1; i <= q; i++) {
    cin >> edge[i + m].from >> edge[i + m].to >> edge[i + m].val;
    edge[i + m].idx = i + m;
  }
  sort (edge + 1, edge + m + q + 1);
  for (int i = 1; i <= m + q; i++) {
    int f1 = root (edge[i].from), f2 = root (edge[i].to);
    if (f1 == f2) {
      if (edge[i].idx > m) {
        ans[edge[i].idx - m] = "No";
        continue;
      }
    }
    if (edge[i].idx > m) {
      ans[edge[i].idx - m] = "Yes";
    } else {
      fath[f1] = f2;
    }
  }
  for (int i = 1; i <= q; i++) {
    cout << ans[i] << '\n';
  }
  return 0;
}