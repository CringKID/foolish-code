#include <iostream>
#include <algorithm>
#include <cstring> 
#include <vector>
#include <set>

using namespace std;
using ll = long long;
using Pii = pair <int, int>;
const int kMaxN = 3e5 + 5, mod = 998244353;

ll dp[kMaxN][2], ans = 1;
int depth[kMaxN], col[kMaxN], fa[kMaxN], n, k;
vector <int> edge[kMaxN];
void DFS (int x, int p = 0) {
  depth[x] = depth[p] + 1;
  fa[x] = p;
  for (int y : edge[x]) {
    if (y == p) {
      continue;
    }
    DFS (y, x);
  }
}
ll quickpow (ll base, ll index) {
  ll ans = 1;
  while (index) {
    if (index & 1) {
      ans = ans * base % mod;
    }
    index >>= 1;
    base = base * base % mod;
  }
  return ans;
}
void solve (int x, int p = 0) {
  dp[x][col[x] != 0] = 1;
  for (int y : edge[x]) {
    if (y == p) {
      continue;
    }
    solve (y, x);
    if (col[x]) {
      dp[x][1] = dp[x][1] * (dp[y][0] + dp[y][1]) % mod;
    } else {
      dp[x][0] = dp[x][0] * (dp[y][0] + dp[y][1]) % mod;
      dp[x][1] = (dp[x][1] + dp[y][1] * quickpow (dp[y][0] + dp[y][1], mod - 2)) % mod;
    }
  }
  if (!col[x]) {
    dp[x][1] = 1ll * dp[x][1] * dp[x][0] % mod;
  }
}
vector <int> ve[kMaxN];
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);
 
  cin >> n >> k;
  for (int i = 1; i <= n; i++) {
    cin >> col[i];
    ve[col[i]].push_back (i);
  }
  for (int i = 1, from, to; i < n; i++) {
    cin >> from >> to;
    edge[from].push_back (to);
    edge[to].push_back (from);
  }
  DFS (1);
  for (int i = 1; i <= k; i++) {
    set <Pii> pq;
    for (int x : ve[i]) {
      pq.emplace (-depth[x], x);
    }
    while (pq.size () > 1) {
      int x = pq.begin () -> second;
      pq.erase (pq.begin ());
      if (!col[x]) {
        col[x] = i;
      }
      if (col[x] != i) {
        cout << 0 << '\n';
        return 0;
      }
      pq.emplace (-depth[x] + 1, fa[x]);
    }
    int x = pq.begin () -> second;
    if (!col[x]) {
      col[x] = i;
    }
    if (col[x] != i) {
      cout << 0 << '\n';
      return 0;
    }
  }
  solve (ve[1].front ());
  cout << dp[ve[1].front ()][1] << '\n';
  return 0;
}