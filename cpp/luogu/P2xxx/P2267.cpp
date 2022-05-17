#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
using ll = long long;
const int kMaxN = 5e5 + 5;

int n, p, arr1[kMaxN], arr2[kMaxN], cur[kMaxN];
ll dp[kMaxN], sum[kMaxN];
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n >> p;
  for (int i = 1; i <= n; i++) {
    cin >> arr1[i], arr2[i] = arr1[i];
  }
  sort (arr2 + 1, arr2 + n + 1);
  int rec = unique (arr2 + 1, arr2 + n + 1) - arr2 - 1;
  for (int i = 1; i <= n; i++) {
    arr1[i] = lower_bound (arr2 + 1, arr2 + rec + 1, arr1[i]) - arr2;
  }
  for (int i = 1; i <= n; i++) {
    cur[arr1[i]] ? dp[i] = (sum[i - 1] - sum[cur[arr1[i]] - 1]) % p : dp[i] = (sum[i - 1] + 1) % p;
    sum[i] = (sum[i - 1] + dp[i]) % p, cur[arr1[i]] = i;
  }
  cout << (sum[n] % p + p) % p << '\n';
  return 0;
}