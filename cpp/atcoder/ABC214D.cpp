#include <iostream>
#include <algorithm>
#include <numeric>

using namespace std;
using ll = long long;
const int kMaxN = 1e5 + 5, kMod = 1e9 + 7;

struct Edge {
  ll from, to, cost;
} edge[kMaxN];
int fath[kMaxN], siz[kMaxN], n;
ll ans;
int root (int x) {
  return fath[x] != x ? fath[x] = root (fath[x]) : fath[x];
}
void merge (int x, int y) {
  siz[root (y)] += siz[root (x)];
  fath[root (x)] = root (y);
}
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n;
  for (int i = 1; i <= n; i++) {
    fath[i] = i, siz[i] = 1;
  }
  fill (siz, siz + n + 1, 1), iota (fath, fath + n + 1, 0);
  for (int i = 0; i < n - 1; i++) {
    cin >> edge[i].from >> edge[i].to >> edge[i].cost;
  }
  sort (edge, edge + n - 1, [] (Edge e1, Edge e2) { return e1.cost < e2.cost; });
  for (int i = 0; i < n - 1; i++) {
    ans += edge[i].cost * siz[root (edge[i].to)] * siz[root (edge[i].from)];
    merge (edge[i].from, edge[i].to);
  }
  cout << ans << '\n';
  return 0;
}