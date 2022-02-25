#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
const int kMaxN = 4e5 + 5, kMod = 998244353;

vector <int> edge[kMaxN];
int n, from, to, dis, plc, ans = 1, dist[kMaxN], fath[kMaxN], arr[kMaxN];
void DFS (int now, int fa) {
  dist[now] = dist[fa] + 1;
  fath[now] = fa;
  for (auto to : edge[now]) {
    if (to != fa) {
      DFS (to, now);
    }
  }
}
void solv (int now, int fa, int opt) {
  dist[now] = dist[fa] + 1;
  if (dist[now] == dis / 2) {
    arr[opt]++;
  }
  for (auto to : edge[now]) {
    if (to != fa) {
      solv (to, now, opt);
    }
  }
}
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n;
  for (int i = 1, from, to; i < n; i++) {
    cin >> from >> to;
    edge[from].push_back (n + i);
    edge[n + i].push_back (from);
    edge[n + i].push_back (to);
    edge[to].push_back (n + i);
  }
  n = n * 2 - 1, dist[0] = -1;
  DFS (1, 0);
  for (int i = 1; i <= n; i++) {
    if (dist[i] > dist[from]) {
      from = i;
    }
  }
  DFS (from, 0);
  for (int i = 1; i <= n; i++) {
    if (dist[i] > dist[to]) {
      to = i;
    }
  }
  dis = dist[to], plc = to;
  for (int i = 1; i <= dis / 2; i++) {
    plc = fath[plc];
  }
  dist[plc] = 0;
  for (auto to : edge[plc]) {
    solv (to, plc, to);
    ans = 1ll * ans * (arr[to] + 1) % kMod;
  }
  ans--;
  for (auto to : edge[plc]) {
    ans = (ans - arr[to] + kMod) % kMod;
  }
  cout << ans << '\n';
  return 0;
}