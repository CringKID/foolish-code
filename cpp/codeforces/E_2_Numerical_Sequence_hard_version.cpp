#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;

ll t, k, arr[25], sum[25], cur[25];
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  for (ll i = 1; i <= 10; i++) {
    ll x = i, l = 1, r = 9;
    for ( ; --x; l *= 10, r = r * 10 + 9) {
    }
    arr[i] = (r - l + 1) * i, sum[i] = sum[i - 1] + arr[i];
    cur[i] = cur[i - 1] + (sum[i - 1] + i + sum[i]) * (r - l + 1) / 2;
  }
  cin >> t; 
  while (t--) {
    cin >> k;
    ll d = lower_bound (cur + 1, cur + 10 + 1, k) - cur, l = 1, r = 9, x = d; k -= cur[d - 1];
    for ( ; --x; l *= 10, r = r * 10 + 9) {
    }
    ll nl = l;
    while (l <= r) {
      ll mid = (l + r) >> 1;
      ((2 * sum[d - 1] + d + (mid - nl + 1) * d) * (mid - nl + 1) / 2 >= k) ? r = mid - 1 : l = mid + 1;
    }
    k -= (2 * sum[d - 1] + d + (l - nl) * d) * (l - nl) / 2;
    d = lower_bound (sum + 1, sum + 10 + 1, k) - sum, k -= sum[d - 1];
    ll ans = 1, num;
    for (ll i = 1; i < d; ans *= 10, i++) {  
    }
    num = (k - 1) / d, k -= num * d, ans += num, k = d - k;
    for ( ; k--; ans /= 10) {
    }
    cout << ans % 10 << '\n';
  }
  return 0;
}