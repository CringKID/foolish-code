#include <algorithm>
#include <iostream>

using namespace std;
using ll = long long;
using Pii = pair<int, int>;
using Pll = pair<ll, ll>;
const int kMaxN = 1e4 + 5, kMod = 1e9 + 7, kInf = 1e9;

ll ans;
int T, n, w, h, len, arr[kMaxN << 1];
struct Star {
  int left, right, high, len;
  bool operator<(const Star& another) const {
    if (high == another.high) {
      return len < another.len;
    }
    return high > another.high;
  }
} star[kMaxN << 1];
struct Node {
  int left, right;
  ll value, lazy;
} tree[kMaxN << 4];
void pushup(int rt) {
  tree[rt].value = max(tree[rt << 1].value, tree[rt << 1 | 1].value);
}
void pushdown(int rt) {
  tree[rt << 1].value += tree[rt].lazy, tree[rt << 1 | 1].value += tree[rt].lazy;
  tree[rt << 1].lazy += tree[rt].lazy, tree[rt << 1 | 1].lazy += tree[rt].lazy;
  tree[rt].lazy = 0;
}

void build(int rt, int left, int right) {
  tree[rt] = (Node){left, right, 0, 0};
  if (left == right) {
    return;
  }
  int mid = left + right >> 1;
  build(rt << 1, left, mid);
  build(rt << 1 | 1, mid + 1, right);
}
void update(int rt, int left, int right, int sum) {
  if (tree[rt].left > right || tree[rt].right < left) {
    return;
  } else if (left <= tree[rt].left && tree[rt].right <= right) {
    tree[rt].value += ll(sum), tree[rt].lazy += ll(sum);
    return pushdown(rt);
  }
  update(rt << 1, left, right, sum);
  update(rt << 1 | 1, left, right, sum);
  pushdown(rt), pushup(rt);
}

int main() {
  ios ::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);

  cin >> T;
  while (T--) {
    cin >> n >> w >> h;
    for (int i = 1; i <= n; i++) {
      int x, y, l;
      cin >> x >> y >> l;
      star[i] = (Star){x, x + w - 1, y, -l};
      star[i + n] = (Star){x, x + w - 1, y + h, l};
      arr[i * 2 - 1] = x;
      arr[i << 1] = x + w - 1;
    }
    sort(arr + 1, arr + n * 2 + 1);
    len = unique(arr + 1, arr + n * 2 + 1) - arr - 1;
    sort(star + 1, star + n * 2 + 1);
    build(1, 1, len);

    ans = 0;
    for (int i = 1; i <= n << 1; i++) {
      int cur1 = lower_bound(arr + 1, arr + len + 1, star[i].left) - arr, cur2 = lower_bound(arr + 1, arr + len + 1, star[i].right) - arr;
      update(1, cur1, cur2, star[i].len);
      ans = max(ans, tree[1].value);
    }
    cout << ans << '\n';
  }
  return 0;
}