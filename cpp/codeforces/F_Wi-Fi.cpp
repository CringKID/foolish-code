#include <iostream>
#include <algorithm>
#include <deque>

using namespace std;
using ll = long long;
const int kMaxN = 4e5 + 5;

char str[kMaxN];
deque <int> que;
ll n, k, dp[kMaxN], ans = LLONG_MAX;
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n >> k >> str + 1, que.push_back (0);
  for (int i = 1; i <= n + k; que.push_back (i++)) {
    dp[i] = dp[i - 1] + i;
    if (i - k >= 1 && str[i - k] == '1') {
      for ( ; !que.empty () && que.front () < i - 2 * k - 1; que.pop_front ()) {
      }
      dp[i] = min (dp[i], dp[que.front ()] + i - k);
    }
    for ( ; !que.empty () && dp[que.back ()] >= dp[i]; que.pop_back ()) {
    }
  }
  for_each (dp + n, dp + n + k + 1, [&] (ll &x) { ans = min (ans, x); });
  cout << ans << '\n';
  return 0;
}