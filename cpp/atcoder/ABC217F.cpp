#include <iostream>
#include <algorithm>

using namespace std;
const int kMaxN = 555, kMod = 998244353;

bool vis[kMaxN][kMaxN];
int n, m, mat[kMaxN][kMaxN], arr[kMaxN], inc[kMaxN], diff[kMaxN], dp[kMaxN][kMaxN];
int C (int a, int b) {
  return 1ll * arr[a] * diff[a - b] % kMod * diff[b] % kMod;
}
int DFS (int l, int r) {
  if (vis[l][r]) {
    return dp[l][r];
  }
  if (l > r) {
    return 1;
  }
  int tmp = 0;
  for (int i = l + 1; i <= r; i += 2) {
    if (mat[l][i]) {
      tmp = (tmp + 1ll * DFS (l + 1, i - 1) * DFS (i + 1, r) % kMod * C ((i - l - 1) / 2 + (r - i) / 2 + 1, (r - i) / 2) % kMod) % kMod; 
    }
  }
  return vis[l][r] = 1, dp[l][r] = tmp;
}
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  arr[0] = arr[1] = inc[0] = diff[0] = inc[1] = diff[1] = 1;
  for (int i = 2; i <= 503; i++) {
    arr[i] = 1ll * arr[i - 1] * i % kMod;
    inc[i] = kMod - 1ll * inc[kMod % i] * (kMod / i) % kMod;
    diff[i] = 1ll * diff[i - 1] * inc[i] % kMod;
  }
  cin >> n >> m;
  for (int i = 1, from, to; i <= m; i++) {
    cin >> from >> to;
    mat[from][to] = 1;
  }
  cout << DFS (1, n * 2) << '\n';
  return 0;
}