#include <iostream>
#include <algorithm>
#include <cstring>
#include <map>

using namespace std;
using ll = long long;
const ll kMaxN = 1e3 + 5, kMaxM = 2e5 + 5;

ll n, m, k, arr[kMaxN], dist[kMaxN][kMaxN], cur[kMaxN], tot, cnt;
struct Edge {
  int from, to, val;
  bool operator < (const Edge &a) const {
    return val < a.val;
  }
} edge[kMaxM];
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n >> m >> k;
  for_each (edge + 1, edge + m + 1, [] (Edge &ed) { cin >> ed.from >> ed.to >> ed.val; }), sort (edge + 1, edge + m + 1);
  for (int i = 1; i <= min (m, k); i++) {
    arr[++tot] = edge[i].from, arr[++tot] = edge[i].to;
  }
  sort (arr + 1, arr + tot + 1), tot = unique (arr + 1, arr + tot + 1) - arr - 1, memset (dist, 0x3f, sizeof (dist));
  for (int i = 1; i <= tot; i++) {
    dist[i][i] = 0;
  }
  for (int i = 1; i <= min (m, k); i++) {
    int s1 = lower_bound (arr + 1, arr + tot + 1, edge[i].from) - arr, s2 = lower_bound (arr + 1, arr + tot + 1, edge[i].to) - arr;
    dist[s1][s2] = dist[s2][s1] = edge[i].val;
  }
  for (int k = 1; k <= tot; k++) {
    for (int i = 1; i <= tot; i++) {
      for (int j = 1; j <= tot; j++) {
        dist[i][j] = min (dist[i][j], dist[i][k] + dist[k][j]);
      }
    }
  }
  for (int i = 1; i <= tot; i++) {
    for (int j = i + 1; j <= tot; j++) {
      cur[++cnt] = dist[i][j];
    }
  }
  sort (cur + 1, cur + cnt + 1);
  cout << cur[k] << '\n';
  return 0;
}