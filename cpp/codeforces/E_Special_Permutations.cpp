#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;
const ll kMaxN = 2e5 + 5;

ll n, m, ans[kMaxN], sum[kMaxN], cur[kMaxN], arr[kMaxN];
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n >> m;
  for_each (arr, arr + m, [&] (ll &x) { cin >> x; });
  for (ll i = 1, mmax, mmin; i < m; i++) {
    mmax = max (arr[i], arr[i - 1]), mmin = min (arr[i], arr[i - 1]);
    ans[1] += mmax - mmin;
    if (mmax == mmin) {
      continue;
    }
    sum[mmin] += mmin - 1, sum[mmax] += mmin * 2 - mmax;
    cur[mmin + 1]--, cur[mmax]++;
  }
  for (ll i = 2; i <= n; i++) {
    cur[i] += cur[i - 1];
  }
  for (ll i = 2; i <= n; i++) {
    ans[i] = ans[1] + sum[i] + cur[i];
  }
  for_each (ans + 1, ans + n + 1, [&] (ll &x) { cout << x << ' '; });
  return 0;
}