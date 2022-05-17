#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;
using ll = long long;

priority_queue <ll> que1, que2;
ll ans = 0, n, x, y, z;
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n >> x >> y >> z;
  for (ll i = 1; i <= n; i++) {
    ll a, b; cin >> a >> b;
    auto solve = [] (priority_queue <ll> &que1, priority_queue <ll> &que2, int x, int i) {
       (!que1.size () || i * z - que1.top () >= x) ? (ans += x, que2.push (i * z + x)) : (ans += i * z - que1.top (), que2.push (i * z * 2 - que1.top ()), que1.pop ());
    };
    for (ll j = 1; j <= (a - b > 0 ? a - b : b - a); j++) {
      a < b ? solve (que1, que2, x, i) : solve (que2, que1, y, i);
    }
  }
  cout << ans << '\n';
  return 0;
}