#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;
const int kMaxN = (1 << 10) + 5, kMod = 998244353;

string str;
ll n, dp[kMaxN][kMaxN][10], rec;
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n >> str;
  for (int i = 1; i <= n; i++) {
    int x = str[i - 1] - 'A';
    for (int sta = 0; sta < 1 << 10; sta++) {
      for (int j = 0; j < 10; j++) {
        dp[i][sta][j] += dp[i - 1][sta][j];
        if (x == j) {
          dp[i][sta][j] = (dp[i][sta][j] + dp[i - 1][sta][j]) % kMod;
        }
        if (!(sta >> x & 1)) {
          dp[i][sta | (1 << x)][x] = (dp[i][sta | (1 << x)][x] + dp[i - 1][sta][j]) % kMod;
        }
      }
    }
    dp[i][1 << x][x] = (dp[i][1 << x][x] + 1) % kMod;
  }
  for (int sta = 0; sta < 1 << 10; sta++) {
    for (int i = 0; i < 10; i++) {
      (rec += dp[n][sta][i]) %= kMod;
    }
  }
  cout << rec << '\n';
  return 0;
}