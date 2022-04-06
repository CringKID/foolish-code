#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
const int kMaxN = 2e5 + 5, kMod = 1e9 + 7;

int n;
string str;
long long dp[kMaxN], ans;
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> str, n = str.size ();
  dp[0] = 1;
  for (int i = 0; i < n; i++) {
    for (int j = i - 1; ; j--) {
      dp[i + 2] = (dp[i + 2] + dp[j + 1]) % kMod;
      if (j == -1 || str[j] == str[i]) {
        break;
      }
    }
  }
  for (int i = 2; i < n + 2; i++) {
    ans += dp[i];
  }
  cout << ans % kMod << '\n';
  return 0;
}