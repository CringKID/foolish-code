#include <iostream>
#include <algorithm>
#include <cstring>
#include <map>

using namespace std;
const int kMaxN = 105, kInf = 0x7fffffff;

string str;
bool edge[kMaxN][kMaxN];
int n, m, dp[kMaxN][kMaxN], pre[kMaxN][kMaxN], type[kMaxN][kMaxN], arr1[kMaxN], arr2[kMaxN], tot;
map <int, string> encode;
map <string, int> decode;
int DFS1 (int x, int y) {
  if (dp[x][y]) {
    return dp[x][y];
  }
  if (x + y == 1) {
    return 0;
  }
  int mmin = min (x, y);
  for (int i = 0; i < mmin; i++) {
    if (edge[i][x]) {
      dp[y][x] = dp[x][y] = max (dp[x][y], DFS1 (i, y) + 1);
    }
    if (edge[i][y]) {
      dp[y][x] = dp[x][y] = max (dp[x][y], DFS1 (i, x) + 1);
    }
  }
  return (!dp[x][y]) ? -kInf : dp[x][y];
}
void DFS2 (int x, int y) {
  arr1[++tot] = x, arr2[tot] = y;
  if (x + y == 1) {
    return ;
  }
  int mmin = min (x, y);
  for (int i = 0; i < mmin; i++) {
    if (dp[i][y] == dp[x][y] - 1 && edge[i][x]) {
      DFS2 (i, y);
      return ;
    }
    if (dp[x][i] == dp[x][y] - 1 && edge[i][y]) {
      DFS2 (x, i);
      return ;
    }
  }
}
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> str;
    encode[i] = str, decode[str] = i;
  }
  for (int i = 1; i <= m; i++) {
    string str1, str2; cin >> str1 >> str2;
    int x = decode[str1], y = decode[str2];
    edge[x][y] = edge[y][x] = true;
    if (x == 1) {
      edge[0][y] = edge[y][0] = true;
    } else if (y == 1) {
      edge[0][x] = edge[x][0] = true;
    }
  }
  DFS1 (n, n);
  if (!dp[n][n]) {
    cout << "No Solution!" << '\n';
    return 0;
  }
  cout << dp[n][n] << '\n';
  for (int i = 1; i < n; i++) {
    if (dp[i][n] == dp[n][n] - 1) {
      DFS2 (i, n); break;
    }
  }
  sort (arr1 + 1, arr1 + tot + 1), sort (arr2 + 1, arr2 + tot + 1);
  int size1 = unique (arr1 + 1, arr1 + tot + 1) - arr1 - 1, size2 = unique (arr2 + 1, arr2 + tot + 1) - arr2 - 1;
  cout << encode[1] << '\n';
  for (int i = 1; i <= size1; i++) {
    if (arr1[i] > 1) {
      cout << encode[arr1[i]] << '\n';
    }
  }
  for (int i = size2; i; i--) {
    if (arr2[i] > 1) {
      cout << encode[arr2[i]] << '\n';
    }
  }
  cout << encode[1] << '\n';
  return 0;
}