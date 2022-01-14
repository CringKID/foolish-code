#include <bits/stdc++.h>

using namespace std;

const int kMaxN = 133333, kMaxM = 3e6 + 5;

int n, m, len, cnt1, cnt2, all, arr1[kMaxN], arr2[kMaxN], ans[kMaxN], sum[kMaxM], que[kMaxN][3];
char opt[15];
struct interval {
  int left, right, value, identity;
  bool operator<(const interval another) const {
    if (left / len == another.left / len) {
      if (right / len == another.right / len) {
        return identity < another.identity;
      } else {
        return right < another.right;
      }
    } else {
      return left < another.left;
    }
  }
} inter[kMaxN];

void add(int now) {
  if ((++sum[now]) == 1) {
    all++;
  }
}
void del(int now) {
  if (!(--sum[now])) {
    all--;
  }
}
int main() {
  ios ::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);

  cin >> n >> m;
  len = pow(n, (double)2.0 / (double)3.0);
  for (int i = 1; i <= n; i++) {
    cin >> arr1[i];
    arr2[i] = arr1[i];
  }
  for (int i = 1, a, b; i <= m; i++) {
    cin >> opt >> a >> b;
    if (opt[0] == 'Q') {
      inter[cnt1].left = a;
      inter[cnt1].right = b;
      inter[cnt1].identity = cnt1;
      inter[cnt1++].value = cnt2;
    } else {
      que[cnt2][0] = a;
      que[cnt2][1] = arr2[a];
      que[cnt2++][2] = arr2[a] = b;
    }
  }
  sort(inter, inter + cnt1);

  add(arr1[1]);
  int left_ = 1, right_ = 1, last = 0;
  for (int i = 0; i < cnt1; i++) {
    for (; last < inter[i].value; last++) {
      if (left_ <= que[last][0] && que[last][0] <= right_) {
        del(que[last][1]);
        add(que[last][2]);
      }
      arr1[que[last][0]] = que[last][2];
    }
    for (; last > inter[i].value; last--) {
      if (left_ <= que[last - 1][0] && que[last - 1][0] <= right_) {
        del(que[last - 1][2]);
        add(que[last - 1][1]);
      }
      arr1[que[last - 1][0]] = que[last - 1][1];
    }

    for (++right_; right_ <= inter[i].right; right_++) {
      add(arr1[right_]);
    }
    for (--right_; right_ > inter[i].right; right_--) {
      del(arr1[right_]);
    }
    for (--left_; left_ >= inter[i].left; left_--) {
      add(arr1[left_]);
    }
    for (++left_; left_ < inter[i].left; left_++) {
      del(arr1[left_]);
    }
    ans[inter[i].identity] = all;
  }

  for (int i = 0; i < cnt1; i++) {
    cout << ans[i] << '\n';
  }
  return 0;
}