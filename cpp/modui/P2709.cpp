#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const ll kMaxN = 5e4 + 5;

ll arr[kMaxN], sum[kMaxN], t, len;

int place (int left) {
  return left / len;
}
struct interval {
  int left, right, value;
  bool operator < (const interval & another) {
    return place (left) == place (another.left) ? right < another.right : left < another.left;
  }
} inter[kMaxN];

ll ans[kMaxN], rec, left_ = 1, right_;
void del (ll now) {
  rec -= 2 * (--sum[arr[now]]) + 1;
}
void add (ll now ) {
  rec += 2 * (++sum[arr[now]]) - 1;
}

int n, m, k;
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n >> m >> k;
  t = sqrt (n);
  len = n / t;
  for (int i = 1; i <= n; i++) {
    cin >> arr[i];
  }
  for (int i = 1; i <= m; i++) {
    cin >> inter[i].left >> inter[i].right;
    inter[i].value = i;
  }
  sort (inter + 1, inter + m + 1);

  for (int i = 1; i <= m; i++) {
    while (left_ < inter[i].left) del (left_++);
    while (left_ > inter[i].left) add (--left_);
    while (right_ < inter[i].right) add (++right_);
    while (right_ > inter[i].right) del (right_--);
    ans[inter[i].value] = rec;
  }

  for (int i = 1; i <= m; i++) {
    cout << ans[i] << '\n';
  }
  return 0;
}