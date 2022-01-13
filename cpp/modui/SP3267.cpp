#include <bits/stdc++.h>

using namespace std;

const int kMaxN = 1.1e6 + 5;

int arr[kMaxN], col[kMaxN], ans, n, m, len, number[kMaxN];  
struct interval {
  int left, right, value, identity;
  bool operator < (const interval & another) const {
    if (!(value ^ another.value)) {
      return (value & 1) ? right < another.right : right > another.right;
    }
    return value < another.value;
  }
} inter[kMaxN];

void del (int cur) {
  if (!(--col[arr[cur]])) {
    ans--;
  }
}
void add (int cur) {
  if ((++col[arr[cur]]) == 1) {
    ans++;
  }
}

int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n;
  len = sqrt (n);
  for (int i = 1; i <= n; i++) {
    cin >> arr[i];
  }
  cin >> m;
  for (int i = 1; i <= m; i++) {
    cin >> inter[i].left >> inter[i].right;
    inter[i].value = (inter[i].left - 1) / len + 1;
    inter[i].identity = i;
  }
  sort (inter + 1, inter + m + 1);

  int left_ = 1, right_ = 0;
  for (int i = 1; i <= m; i++) {
    while (left_ < inter[i].left) {
      del (left_++);
    }
    while (left_ > inter[i].left) {
      add (--left_);
    }
    while (right_ < inter[i].right) {
      add (++right_);
    }
    while (right_ > inter[i].right) {
      del (right_--);
    }
    number[inter[i].identity] = ans;
  }

  for (int i = 1; i <= m; i++) {
    cout << number[i] << '\n';
  }
  return 0;
}