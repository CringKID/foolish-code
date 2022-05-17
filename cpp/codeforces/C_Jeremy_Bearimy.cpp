#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;
const int kMaxN = 2e5 + 5;

struct Edge {
  int to, next;
  ll val;
} ed[kMaxN << 1];
ll ans, siz[kMaxN], res;
int head[kMaxN], tot, T, n;
void add (int from, int to, ll val) {
  ed[++tot] = {to, head[from], val}, head[from] = tot;
}
void DFS (int x, int fa) {
  siz[x] = 1;
  for (int i = head[x]; i; i = ed[i].next) {
    int to = ed[i].to;
    if (to == fa) {
      continue;
    }
    DFS (to, x), siz[x] += siz[to];
    siz[to] & 1 ? ans += ed[i].val : 0;
    res += min (siz[to], n - siz[to]) * ed[i].val;
  }
}
int main () {
  for (cin >> T; T; T--) {
    cin >> n, n <<= 1;
    fill (head, head + n + 1, 0), fill (siz, siz + n + 1, 0);
    tot = 0;
    for (int i = 1, from, to; i < n; i++) {
      ll val; cin >> from >> to >> val;
      add (from, to, val), add (to, from, val);
    }
    ans = res = 0, DFS (1, 0);
    cout << ans << ' ' << res << '\n';
  }
  return 0;
}