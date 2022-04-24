#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;
using Pii = pair <int, int>;
using Pll = pair <ll, ll>;
const int kMaxN = 5e5 + 5, kMod = 1e9 + 7, kInf = 1e9;

int tree[kMaxN], n, m;
void update (int x, int val) {
  for (int i = x; i <= n; tree[i] += val, i += i & -i) {
  }
}
int query (int x) {
  int rec = 0;
  for (int i = x; i; rec += tree[i], i -= i & -i) {
  }
  return rec;
}
//#define contest
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);
#ifdef contest
  freopen (, , stdin);
  freopen (, , stdout);
#endif

  cin >> n >> m;
  for (int i = 1, x; i <= n; i++) {
    cin >> x;
    update (i, x);
  }
  for (int i = 1, opt, x, y; i <= m; i++) {
    cin >> opt >> x >> y;
    if (opt == 1) {
      update (x, y);
    } else {
      cout << query (y) - query (x - 1) << '\n';
    }
  }
  return 0;
}