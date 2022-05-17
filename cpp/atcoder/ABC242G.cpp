#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;
const int kMaxN = 1e5 + 5;
int n, m, arr[kMaxN], cur[kMaxN], rec, ans[kMaxN * 10], b, l = 1, r;
struct Interval {
  int l, r;
  mutable int val;
  bool operator < (const Interval &p) {
    return (l / b != p.l / b ? l < p.l : r < p.r);
  }
} inter[kMaxN * 10];
void add (int x) {
  rec += (cur[x]++) & 1;
}
void del (int x) {
  rec -= (--cur[x]) & 1;
}
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n;
  for_each (arr + 1, arr + n + 1, [&] (int &x) { cin >> x; });
  cin >> m;
  for (int i = 1; i <= m; i++) {
    cin >> inter[i].l >> inter[i].r;
    inter[i].val = i;
  }
  b = 500, sort (inter + 1, inter + m + 1);
  for (int i = 1, l_, r_; i <= m; i++) {
    l_ = inter[i].l, r_ = inter[i].r;
    for ( ; r < r_; add (arr[++r])) {}
    for ( ; l > l_; add (arr[--l])) {}
    for ( ; r > r_; del (arr[r--])) {}
    for ( ; l < l_; del (arr[l++])) {}
    ans[inter[i].val] = rec;
  }
  for_each (ans + 1, ans + m + 1, [&] (int x) { cout << x << '\n'; });
  return 0;
}