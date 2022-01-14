#include <bits/stdc++.h>

using std :: sort;
using std :: lower_bound;
using std :: unique;
using std :: cin;
using std :: cout;
using std :: ios;

const int kMaxN = 2e5 + 5;

int arr[kMaxN], temp[kMaxN], tl[kMaxN], tr[kMaxN], belong[kMaxN];
struct interval {
  int left, right, identity;
  bool operator < (const interval & another) {
    return belong[left] == belong[another.left] ? right < another.right : left < another.left;
  }
} inter[kMaxN];

template <class type> type max (type a, type b) {return a < b ? b : a;}
template <class type> type min (type a, type b) {return a > b ? b : a;}

int cnt[kMaxN];
int64_t tmp;

void add (int now, int cur = 1) {
  cnt[arr[now]] += cur;
  tmp = max (tmp, (int64_t)cnt[arr[now]] * temp[arr[now]]);
}
int64_t brute (int left_, int right_) {
  static int oop[kMaxN];
  int64_t ans = 0;
  for (int i = left_; i <= right_; i++) {
    oop[arr[i]]++;
  }
  for (int i = left_; i <= right_; i++) {
    ans = max (ans, (int64_t)oop[arr[i]] * temp[arr[i]]);
  }
  for (int i = left_; i <= right_; i++) {
    oop[arr[i]]--;
  }
  return ans;
}

int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  int n, q;
  cin >> n >> q;
  for (int i = 1; i <= n; i++) {
    cin >> arr[i];
    temp[i] = arr[i];
  }
  for (int i = 1; i <= q; i++) {
    cin >> inter[i].left >> inter[i].right;
    inter[i].identity = i;
  }
  sort (temp + 1, temp + n + 1);
  int len = unique (temp + 1, temp + n + 1) - temp - 1;
  for (int i = 1; i <= n; i++) {
    arr[i] = lower_bound (temp + 1, temp + len + 1, arr[i]) - temp;
  }

  int blocklen = sqrt (n), block = n / blocklen;
  for (int i = 1; i <= block; i++) {
    tl[i] = tr[i - 1] + 1;
    tr[i] = tl[i] + blocklen - 1;
  }
  if (tr[block] < n) {
    block++;
    tl[block] = tr[block - 1] + 1;
    tr[block] = n;
  }
  for (int i = 1; i <= n; i++) {
    belong[i] = (i - 1) / blocklen + 1;
  }
  
  sort (inter + 1, inter + q + 1);
  static int64_t ans[kMaxN];
  for (int i = 1, cur = 1, left_ = 0, right_ = 0; i <= block; i++) {
    memset (cnt, 0, sizeof (cnt));
    right_ = tr[i];
    tmp = 0;

    while (belong[inter[cur].left] == i) {
      left_ = tr[i] + 1;
      if (inter[cur].right - inter[cur].left <= blocklen) {
        ans[inter[cur].identity] = brute (inter[cur].left, inter[cur].right);
        cur++;
        continue;
      }

      while (inter[cur].right > right_) {
        add (++right_);
      }
      int64_t now = tmp;
      while (left_ > inter[cur].left) {
        add (--left_);
      }
      ans[inter[cur].identity] = tmp;
      tmp = now;
      while (left_ <= tr[i]) {
        cnt[arr[left_++]]--;
      }
      cur++;
    }
  }
  
  for (int i = 1; i <= q; i++) {
    cout << ans[i] << '\n';
  }
  return 0;
}