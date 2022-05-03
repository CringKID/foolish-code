#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;
const int kMaxN = 2e5 + 5;

int n, m, root[kMaxN], arr[kMaxN], res[kMaxN], tot, p;
struct Node {
  int val, son[2];
} tr[kMaxN << 5];
void build (int &x, int l, int r) {
  x = ++tot;
  if (l == r) {
    return ;
  }
  int mid = l + r >> 1;
  build (tr[x].son[0], l, mid);
  build (tr[x].son[1], mid + 1, r);
}
int update (int x, int l, int r) {
  int level = ++tot; tr[level] = tr[x], tr[level].val++;
  if (l == r) {
    return level;
  }
  int mid = l + r >> 1;
  if (p <= mid) {
    tr[level].son[0] = update (tr[level].son[0], l, mid);
  } else {
    tr[level].son[1] = update (tr[level].son[1], mid + 1, r);
  }
  return level;
}
int query (int x, int y, int l, int r, int k) {
  int mid = l + r >> 1, cur = tr[tr[y].son[0]].val - tr[tr[x].son[0]].val, ans;
  if (l == r) {
    return l;
  }
  if (cur >= k) {
    ans = query (tr[x].son[0], tr[y].son[0], l, mid, k);
  } else {
    ans = query (tr[x].son[1], tr[y].son[1], mid + 1, r, k - cur);
  }
  return ans;
}
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> arr[i], res[i] = arr[i];
  }
  sort (res + 1, res + n + 1);
  int len = unique (res + 1, res + n + 1) - res - 1;
  build (root[0], 1, len);
  for (int i = 1; i <= n; i++) {
    p = lower_bound (res + 1, res + len + 1, arr[i]) - res;
    root[i] = update (root[i - 1], 1, len);
  }
  for (int l, r, k; m; m--) {
    cin >> l >> r >> k;
    int tmp = query (root[l - 1], root[r], 1, len, k);
    cout << res[tmp] << '\n';
  }
  return 0;
}