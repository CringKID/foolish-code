#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;
const ll kMaxN = 1e5 + 5;

ll n, k, ans, arr[kMaxN];
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n >> k;
  for (ll i = 0; i < n; i++) {
    cin >> arr[i];
  }
  sort (arr, arr + n, [] (ll x, ll y) { return x > y; });
  arr[n] = 0;
  for (ll i = 0; i < n; i++) {
    if (k < (arr[i] - arr[i + 1]) * (i + 1)) {
      ll x = k / (i + 1), y = k % (i + 1);
      ans += (arr[i] * 2 - x + 1) * x * (i + 1) / 2, ans += (arr[i] - x) * y;
      break;
    }
    ans += (arr[i] + arr[i + 1] + 1) * (arr[i] - arr[i + 1]) / 2 * (i + 1);
    k -= (arr[i] - arr[i + 1]) * (i + 1);
  }
  cout << ans << '\n';
  return 0;
}