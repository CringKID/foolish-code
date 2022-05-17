#include <iostream>
#include <algorithm>

using namespace std;
const int kMaxN = 2e5 + 5;

int l, n, arr[kMaxN];
string s, st[kMaxN], dp[kMaxN];
bool check (int p, int t) {
  for (int i = 0; i < arr[t]; i++) {
    if (s[p + i] != st[t][i] && s[p + i] != '?') {
      return false;
    }
  }
  return true;
}
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> l >> n >> s;
  for (int i = 1; i <= n; i++) {
    cin >> st[i], arr[i] = st[i].size ();
  }
  for (int i = 1; i <= l; i++) {
    for (int j = 1; j <= n; j++) {
      if (arr[j] > i || !check (i - arr[j], j) || (dp[i - arr[j]] == "" && (i - arr[j]) > 0)) {
        continue;
      }
      (dp[i] == "" || dp[i - arr[j]] + st[j] < dp[i]) ? (dp[i] = dp[i - arr[j]] + st[j]) : 0;
    }
  }
  cout << dp[l] << '\n';
  return 0;
}