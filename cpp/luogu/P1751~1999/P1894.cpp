#include <bits/stdc++.h>

using namespace std;
const int kMaxN = 255;

int n, m, arr[kMaxN], matrix[kMaxN][kMaxN], ans;
bool vis[kMaxN];
bool DFS(int now) {
  for (int i = 1; i <= n; i++) {
    if (!vis[i] && matrix[now][i] && (vis[i] = 1)) {
      if ((!arr[i] || DFS(arr[i])) && (arr[i] = now)) {
        return true;
      }
    }
  }
  return false;
}

int main() {
  ios ::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);

  cin >> n >> m;
  for (int i = 1, sum, tmp; i <= n; i++) {
    cin >> sum;
    while (sum--) {
      cin >> tmp;
      matrix[i][tmp] = 1;
    }
  }
  for (int i = 1; i <= n; i++) {
    memset(vis, false, sizeof(vis));
    ans += DFS(i);
  }
  cout << ans << '\n';
  return 0;
}