#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;
using Pii = pair <int, int>;
using Pll = pair <ll, ll>;
const int kMaxN = 1e6 + 5, kMod = 1e9 + 7, kInf = 1e9;

int n, tot;
ll x1, fuck1, x2, y2, arr[kMaxN << 1];
struct ScanLine {
  ll left, right, high;
  int tag;
  bool operator < (const ScanLine & another) const {
    return high < another.high;
  }
} line[kMaxN << 1];
struct Node {
  int left, right, value;
  ll len;
} tree[kMaxN << 2];
void pushup (int rt) {
  if (tree[rt].value) {
    tree[rt].len = arr[tree[rt].right + 1] - arr[tree[rt].left];
  } else {
    tree[rt].len = tree[rt << 1].len + tree[rt << 1 | 1].len;
  }
}

void build (int rt, int left, int right) {
  tree[rt] = (Node) {left, right, 0, 0};
  if (left == right) {
    return ;
  }
  int mid = left + right >> 1;
  build (rt << 1, left, mid);
  build (rt << 1 | 1, mid + 1, right);
}
void update (int rt, ll left, ll right, int sum) {
  if (arr[tree[rt].right + 1] <= left || right <= arr[tree[rt].left]) {
    return ;
  } else if (left <= arr[tree[rt].left] && arr[tree[rt].right + 1] <= right) {
    tree[rt].value += sum;
    return pushup (rt);
  }
  update (rt << 1, left, right, sum);
  update (rt << 1 | 1, left, right, sum);
  pushup (rt);
}

int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> x1 >> fuck1 >> x2 >> y2;
    arr[i * 2 - 1] = x1, arr[i << 1] = x2;
    line[i * 2 - 1] = (ScanLine) {x1, x2, fuck1, 1};
    line[i << 1] = (ScanLine) {x1, x2, y2, -1};
  }
  n <<= 1, sort (line + 1, line + n + 1), sort (arr + 1, arr + n + 1);
  int len = unique (arr + 1, arr + n + 1) - arr - 1;
  build (1, 1, len - 1);
  ll ans = 0;
  for (int i = 1; i < n; i++) {
    update (1, line[i].left, line[i].right, line[i].tag);
    ans += tree[1].len * (line[i + 1].high - line[i].high);
  }
  cout << ans << '\n';
  return 0;
}