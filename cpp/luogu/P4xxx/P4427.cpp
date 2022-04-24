#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
using ll = long long;
using Pii = pair <int, int>;
using Pll = pair <ll, ll>;
const int kMaxL = 20, kMaxN = 3e5 + 5, kMaxK = 55, kMod = 998244353, kInf = 1e9;

struct Node {
  int fath[kMaxL], dep = -1;
  vector <int> ed;
} node[kMaxN];
int n, m, x, y, z, k, mat[kMaxN][kMaxK];
void walk (int x, int fa) {
  node[x].fath[0] = fa, node[x].dep = node[fa].dep + 1;
  for (int i = 0; i < kMaxL - 1; i++) {
    node[x].fath[i + 1] = node[node[x].fath[i]].fath[i];
  }
  for (int to : node[x].ed) {
    if (to != fa) {
      walk (to, x);
    }
  }
}
int lca (int x, int y) {
  if (node[x].dep > node[y].dep) {
    swap (x, y);
  }
  for (int i = 0; i < kMaxL; i++) {
    if ((node[y].dep - node[x].dep) >> i & 1) {
      y = node[y].fath[i];
    }
  }
  for (int i = kMaxL - 1; i >= 0; i--) {
    if (node[x].fath[i] != node[y].fath[i]) {
      x = node[x].fath[i], y = node[y].fath[i];
    }
  }
  return x == y ? x : node[x].fath[0];
}
//#define contest
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);
#ifdef contest
  freopen (, , stdin);
  freopen (, , stdout);
#endif

  cin >> n;
  for (int i = 1; i < n; i++) {
    cin >> x >> y;
    node[x].ed.push_back (y), node[y].ed.push_back (x);
  }
  for (int i = 1; i <= n; i++) {
    ll val = 1;
    for (ll j = 0; j < kMaxK; j++) {
      mat[i][j] = (mat[i - 1][j] + val) % kMod;
      val = val * i % kMod;
    }
  }
  walk (1, 0);
  cin >> m;
  for (int i = 1; i <= m; i++) {
    cin >> x >> y >> k;
    z = lca (x, y);
    ll ans = mat[node[x].dep][k] + mat[node[y].dep][k] - mat[node[z].dep][k] - (node[z].dep ? mat[node[z].dep - 1][k] : 0);
    cout << (ans + kMod * 2) % kMod << '\n';
  }
  return 0;
}