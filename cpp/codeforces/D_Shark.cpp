#include <iostream>
#include <algorithm>
#include <numeric>
#include <set>

using namespace std;
using Pii = pair <int, int>;
const int kN = 1e5 + 5, kInf = 0x3f3f3f3f;

Pii p[kN];
set <int> Set;
int n, pre[kN], cnt[kN], vis[kN], ss[kN], ans = kInf, len = 1;
bool check () {
  return ss[cnt[*Set.begin ()]] == Set.size ();
}
int root (int x) {
  return x == pre[x] ? x : pre[x] = root (pre[x]);
}
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n;
  fill (cnt + 1, cnt + n + 1, 1), iota (pre + 1, pre + n + 1, 1);
  for (int i = 1; i <= n; i++) {
    cin >> p[i].first, p[i].second = i;
    ans = min (ans, p[i].first + 1);
  }
  sort (p + 1, p + n + 1);
  for (int i = 1; i <= n; i++) {
    int now = p[i].second, f = 0; vis[now] = 1;
    if (now + 1 <= n && vis[now + 1]) {
      int t = root (now), y = root (now + 1);
      pre[t] = y, ss[cnt[y]]--;
      cnt[y] += cnt[t], ss[cnt[y]]++, f = 1;
    }
    if (now - 1 >= 1 && vis[now - 1]) {
      int t = root (now), y = root (now - 1);
      f == 1 ? Set.erase (t), ss[cnt[t]]-- : 0;
      ss[cnt[y]]--, cnt[y] += cnt[t];
      ss[cnt[y]]++, pre[t] = y, f = 2;
    }
    !f ? Set.insert (now), ss[cnt[now]]++ : 0;
    Set.size () > len && check () ? len = Set.size (), ans = p[i].first + 1 : 0;
  }
  cout << ans << '\n';
  return 0;
}