#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;
using Pii = pair <int, int>;
using Pll = pair <ll, ll>;
const int kMaxN = 405, kMaxM = 8e4 + 5;

struct Edge {
  int to, next;
} edge[kMaxM];
int head[kMaxM], tot, ans, cur[kMaxN], n, T;
bool vis[kMaxN];
void add (int from, int to) {
  edge[++tot] = {to, head[from]};
  head[from] = tot;
}
bool DFS (int now) {
  for (int i = head[now], to; i; i = edge[i].next) {
    to = edge[i].to;
    if (!vis[to]) {
      vis[to] = 1;
      if (!cur[to] || DFS (cur[to])) {
        cur[to] = now;
        return true;
      }
    }
  }
  return false;
}
//#define contest
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);
#ifdef contest
  freopen (, , stdin);
  freopen (, , stdout);
#endif

  cin >> T;
  while (T--) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
      for (int j = 1, k; j <= n; j++) {
        cin >> k;
        if (k == 1) {
          add (i, j + n);
        }
      }
    }
    for (int i = 1; i <= n; i++) {
      fill (vis, vis + n * 2 + 1, false);
      if (DFS (i)) {
        ans++;
      }
    }
    if (ans >= n) {
      cout << "Yes" << '\n';
    } else {
      cout << "No" << '\n';
    }
    for (int i = 1; i <= tot; i++) {
      edge[i] = {0, 0}, head[i] = 0;
    }
    ans = tot = 0;
    for (int i = 0; i <= n * 2; i++) {
      cur[i] = 0;
    }
  }
  return 0;
}