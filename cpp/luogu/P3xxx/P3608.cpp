#include <iostream>
#include <algorithm>

using namespace std;
const int kMaxN = 1e6 + 5;

int n, tree[kMaxN], ans;
pair <int, int> P[kMaxN];
void update (int x, int k) {
  for ( ; x <= n; x += x & -x) {
    tree[x] += k;
  }
}
int query (int x) {
  int ans = 0;
  for ( ; x; x -= x & -x) {
    ans += tree[x];
  }
  return ans;
}
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> P[i].first;
    P[i].second = i;
  }
  sort (P + 1, P + n + 1, greater <pair <int, int> > ());
  for (int i = 1; i <= n; i++) {
    update (P[i].second, 1);
    int l = query (P[i].second - 1), r = i - l - 1;
    if (max (l, r) > 2 * min (l, r)) {
      ans++;
    }
  }
  cout << ans << '\n';
  return 0;
}