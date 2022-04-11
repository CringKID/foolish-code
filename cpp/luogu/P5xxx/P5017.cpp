#include <iostream>
#include <algorithm>
#include <cstring>
#include <climits>

using namespace std;
const int kMaxN = 4e6 + 5;
const double kEps = 1e-7;

int n, m, cnt[kMaxN], sum[kMaxN], dp[kMaxN], mmax, tail, head = 1, que[kMaxN], ans = INT_MAX;
double solve (int x, int y) {
  return double (sum[y] + dp[y] - sum[x] - dp[x]) * 1.0 / (cnt[y] == cnt[x] ? kEps : cnt[y] - cnt[x]);
}
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n >> m;
  for (int i = 1, x; i <= n; i++) {
    cin >> x, mmax = max (mmax, x);
    cnt[x]++, sum[x] += x;
  }
  for (int i = 1; i <= mmax + m; i++) {
    cnt[i] += cnt[i - 1], sum[i] += sum[i - 1];
  }
  memset (dp, 0x7f, sizeof (dp)), dp[0] = 0;
  for (int i = 1; i <= mmax + m; i++) {
    for ( ; tail > head && solve (que[tail - 1], que[tail]) > solve (que[tail], i - m); tail--) {
    }
    if (i - m >= 0) {
      que[++tail] = i - m;
    }
    for ( ; tail > head && solve (que[head], que[head + 1]) <= double (i); head++) {
    }
    dp[i] = cnt[i] * i - sum[i];
    if (i - m >= 0) {
      dp[i] = min (dp[que[head]] + i * (cnt[i] - cnt[que[head]]) - sum[i] + sum[que[head]], dp[i]);
    }
  }
  for (int i = mmax; i <= mmax + m; i++) {
    ans = min (ans, dp[i]);
  }
  cout << ans << '\n';
  return 0;
}