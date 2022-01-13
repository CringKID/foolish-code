#include <bits/stdc++.h>

using namespace std;

const int kMaxN = 2e5 + 5, kInf = 1 << 30;

int n, m, k, arr[kMaxN], temp[kMaxN], size_, block, belong[kMaxN], tl[kMaxN], tr[kMaxN], ans[kMaxN];
struct interval {
  int left, right, identity;
  friend bool operator<(interval inter1, interval inter2) {
    if (belong[inter1.left] == belong[inter2.left]) {
      return inter1.right < inter2.right;
    } else {
      return inter1.left < inter2.left;
    }
  }
} inter[kMaxN];
int left1[kMaxN], right1[kMaxN], left2[kMaxN], right2[kMaxN], left3[kMaxN], right3[kMaxN], tmp, all;

int brute(int left_, int right_) {
  for (int i = left_; i <= right_; i++) {
    left3[arr[i]] = kInf;
    right3[arr[i]] = 0;
  }
  int reg = 0;
  for (int i = left_; i <= right_; i++) {
    left3[arr[i]] = min(left3[arr[i]], i);
    right3[arr[i]] = i;
    reg = max(reg, right3[arr[i]] - left3[arr[i]]);
  }
  return reg;
}
void addright(int now) {
  left1[arr[now]] = min(left1[arr[now]], now);
  right1[arr[now]] = now;
  tmp = max(tmp, right1[arr[now]] - left1[arr[now]]);
}
void addleft(int now) {
  left1[arr[now]] = now;
  right1[arr[now]] = max(right1[arr[now]], now);
  tmp = max(tmp, right1[arr[now]] - left1[arr[now]]);
}

int main() {
  ios ::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);

  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> arr[i];
    temp[i] = arr[i];
  }
  sort(temp + 1, temp + n + 1);
  k = unique(temp + 1, temp + n + 1) - temp - 1;
  for (int i = 1; i <= n; i++) {
    arr[i] = lower_bound(temp + 1, temp + k + 1, arr[i]) - temp;
  }

  size_ = 3 * (int)sqrt(n) / 4;
  block = n / size_;
  for (int i = 1; i <= block; i++) {
    tl[i] = tr[i - 1] + 1;
    tr[i] = tl[i] + size_ - 1;
  }
  if (tr[block] < n) {
    block++;
    tl[block] = tl[block - 1] + 1;
    tr[block] = n;
  }
  for (int i = 1; i <= n; i++) {
    belong[i] = (i - 1) / size_ + 1;
  }

  cin >> m;
  for (int i = 1; i <= m; i++) {
    cin >> inter[i].left >> inter[i].right;
    inter[i].identity = i;
  }
  sort(inter + 1, inter + m + 1);

  int cur = 1, left_ = 0, right_ = 0;
  for (int t = 1; t <= block; t++) {
    right_ = tr[t];
    tmp = 0;
    for (int i = 1; i <= k; i++) {
      left1[i] = kInf;
      right1[i] = 0;
    }

    while (belong[inter[cur].left] == t) {
      left_ = tr[t] + 1;
      if (inter[cur].right - inter[cur].left <= size_) {
        ans[inter[cur].identity] = brute(inter[cur].left, inter[cur].right);
        cur++;
        continue;
      }
      while (right_ < inter[cur].right) {
        addright(++right_);
      }

      all = tmp;
      for (int i = inter[cur].left; i <= tr[t]; i++) {
        left2[arr[i]] = left1[arr[i]];
        right2[arr[i]] = right1[arr[i]];
      }
      while (left_ > inter[cur].left) {
        addleft(--left_);
      }
      ans[inter[cur].identity] = tmp;
      tmp = all;
      cur++;
      for (int i = left_; i <= tr[t]; i++) {
        left1[arr[i]] = left2[arr[i]];
        right1[arr[i]] = right2[arr[i]];
      }
    }
  }

  for (int i = 1; i <= m; i++) {
    cout << ans[i] << '\n';
  }
  return 0;
}