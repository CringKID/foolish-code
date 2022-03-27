#include <iostream>
#include <algorithm>

using namespace std;
const int kMaxN = 5e3 + 5;

int n, k, arr[kMaxN], dp[kMaxN][kMaxN];
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n >> k;
  for (int i = 1; i <= n; i++) {
    cin >> arr[i];
  }
  sort (arr + 1, arr + n + 1);
  int cur = 1;
  for (int i = 1; i <= n; i++) {
    for ( ; arr[cur] + 5 < arr[i]; cur++) {
    }
    for (int j = 0; j <= k; dp[i][j] = dp[i - 1][j], j++) {
    }
    for (int j = 1; j <= k; dp[i][j] = max (dp[i][j], dp[cur - 1][j - 1] + (i - cur + 1)), j++) {
    }
    for (int j = 1; j <= k; dp[i][j] = max (dp[i][j - 1], dp[i][j]), j++) {
    }
  }
  cout << dp[n][k] << '\n';
  return 0;
}