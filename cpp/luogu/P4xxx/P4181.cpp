#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;
using ll = long long;
using Pii = pair <int, int>;
const int kMaxN = 1e5 + 5;

ll ans;
Pii shop[kMaxN];
priority_queue <Pii> que;
int n, m, r, buy[kMaxN], cow[kMaxN];
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n >> m >> r;
  for_each (cow + 1, cow + n + 1, [&] (int &x) { cin >> x; });
  for_each (shop + 1, shop + m + 1, [&] (Pii &p) { cin >> p.second >> p.first, que.push (p); });
  for_each (buy + 1, buy + r + 1, [&] (int &x) { cin >> x; });
  sort (cow + 1, cow + n + 1), sort (buy + 1, buy + r + 1);
  for (ll i = 1, tmp = -1, l = 1, r = n, cur = r; i <= n; i++) {
    if (tmp == -1) {
      while (!que.empty() && cow[r]) {
        tmp == -1 ? tmp = 0 : 0;
        if (que.top ().second > cow[r]) {
          Pii x = que.top (); que.pop ();
          tmp += 1LL * cow[r] * x.first, x.second -= cow[r], cow[r] = 0;
          que.push (x);
        } else {
          tmp += 1LL * que.top ().first * que.top ().second, cow[r] -= que.top ().second, que.pop ();
        }
      }
    }
    (~tmp && tmp >= buy[cur] ? (ans += tmp, tmp = -1, r--) : (cur ? ans += buy[cur--], l++ : 0));
  }
  cout << ans << '\n';
  return 0;
}