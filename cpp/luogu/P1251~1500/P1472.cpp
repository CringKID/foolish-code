#include <bits/stdc++.h>

using namespace std;

const int kMod = 9901;
int dp[255][155], n, k;

int main() {
  ios ::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);

  cin >> n >> k;
  for (int i = 1; i <= k; i++) {
    dp[1][i] = 1;
  }
  for (int K = 1; K <= k; K++) {
    for (int i = 3; i <= n; i += 2) {
      for (int j = 1; j < i; j += 2) {
        dp[i][K] = (dp[i][K] + dp[j][K - 1] * dp[i - j - 1][K - 1]) % kMod;
      }
    }
  }
  cout << (dp[n][k] - dp[n][k - 1] + kMod) % kMod;
  return 0;
}