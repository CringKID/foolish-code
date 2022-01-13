#include <bits/stdc++.h>

using namespace std;

const int kMaxN = 1e5 + 5;

int n, m, left_, right_, k, len, block, tot1, tot2, arr1[kMaxN], arr2[kMaxN << 1], 
  place[kMaxN], cnt[kMaxN << 1], tot[kMaxN], ans[kMaxN], opt;
struct interval {
  int left, right, value, identity;
  bool operator < (const interval & another) const {
    if (place[left] ^ place[another.left]) {
      return place[left] < place[another.left];
    } else if (place[right] ^ place[another.right]) {
      return (place[left] & 1 ? right < another.right : right > another.right);
    } else {
      return value < another.value;
    }
  }
} inter[kMaxN];
struct query {
  int pos, value;
} que[kMaxN];

void add (int now) {
  tot[cnt[now]]--;
  tot[++cnt[now]]++;
}
void del (int now) {
  tot[cnt[now]]--;
  tot[--cnt[now]]++;
}
void modify (int now) {
  if (que[now].pos >= left_ && que[now].pos <= right_) {
    del (arr1[que[now].pos]);
    add (que[now].value);
  }
  swap (arr1[que[now].pos], que[now].value);
}

int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  left_ = 1, right_ = 0, k = 0, block = 2154;
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> arr1[i];
    arr2[++len] = arr1[i];
    place[i] = (i - 1) / block + 1;
  }
  for (int i = 1; i <= m; i++) {
    cin >> opt;
    if (opt == 1) {
      tot2++;
      inter[tot2].identity = tot2;
      inter[tot2].value = tot1;
      cin >> inter[tot2].left >> inter[tot2].right;
    } else {
      tot1++;
      cin >> que[tot1].pos >> que[tot1].value;
      arr2[++len] = que[tot1].value;
    }
  }
  
  stable_sort (arr2 + 1, arr2 + len + 1);
  int size_ = unique (arr2 + 1, arr2 + len + 1) - arr2 - 1;
  for (int i = 1; i <= n; i++) {
    arr1[i] = lower_bound (arr2 + 1, arr2 + size_ + 1, arr1[i]) - arr2;
  }
  for (int i = 1; i <= tot1; i++) {
    que[i].value = lower_bound (arr2 + 1, arr2 + size_ + 1, que[i].value) - arr2;
  }

  stable_sort (inter + 1, inter + tot2 + 1);
  for (int i = 1; i <= tot2; i++) {
    while (left_ > inter[i].left) {
      add (arr1[--left_]);
    }
    while (right_ < inter[i].right) {
      add (arr1[++right_]);
    }
    while (left_ < inter[i].left) {
      del (arr1[left_++]);
    }
    while (right_ > inter[i].right) {
      del (arr1[right_--]);
    }
    while (k < inter[i].value) {
      modify (++k);
    }
    while (k > inter[i].value) {
      modify (k--);
    }

    ans[inter[i].identity] = 1;
    while (tot[ans[inter[i].identity]] > 0) {
      ans[inter[i].identity]++;
    }
  }

  for (int i = 1; i <= tot2; i++) {
    cout << ans[i] << '\n';
  }
  return 0;
}