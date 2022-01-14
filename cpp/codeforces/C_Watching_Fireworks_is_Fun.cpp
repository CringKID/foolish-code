#include <bits/stdc++.h>

using namespace std;
using ll = long long;
const int kMaxN = 1.5e5 + 5, kInf = 0x3f3f3f3f;

ll n, m, d, sum, A[kMaxN], B[kMaxN], T[kMaxN], dp[2][kMaxN], que[kMaxN], ans = kInf;
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n >> m >> d;
  memset (dp, kInf, sizeof (dp));
  for (int i = 1; i <= m; i++) {
    cin >> A[i] >> B[i] >> T[i];
    sum += B[i];
  }
  for (int i = 1; i <= n; i++) {
    dp[1][i] = abs (A[1] - i);
  }
  for (int i = 2; i <= m; i++) {
    int now = i & 1, pre = i & 1 ^ 1, cur = T[i] - T[i - 1], head = 1, tail = 0;
    memset (dp[now], kInf, sizeof (dp[now]));
    for (int j = 1; j <= n; j++) {
      for ( ; head <= tail && que[head] < j - cur * d; head++) {
      }
      for ( ; head <= tail && dp[pre][que[tail]] > dp[pre][j]; tail--) {
      }
      que[++tail] = j;
      dp[now][j] = min (dp[now][j], dp[pre][que[head]] + abs (A[i] - j));
    }
    head = 1, tail = 0;
    for (int j = n; j >= 1; j--) {
      for ( ; head <= tail && que[head] > j + cur * d; head++) {
      }
      for ( ; head <= tail && dp[pre][que[head]] > dp[pre][j]; tail--) {
      }
      que[++tail] = j;
      dp[now][j] = min (dp[now][j], dp[pre][que[head]] + abs (A[i] - j));
    }
  }
  for (int i = 1; i <= n; i++) {
    ans = min (ans, dp[m & 1][i]);
  }
  cout << sum - ans << '\n';
  return 0;
}