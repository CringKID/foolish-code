#include <bits/stdc++.h>

using namespace std;

const int kMaxN = 2e5 + 10;

int arr1[kMaxN], arr2[kMaxN], all, ans[kMaxN], cnt1[kMaxN], cnt2[kMaxN], n, m, len1, len2;
struct interval {
  int left, right, value, identity;
} inter[kMaxN];
bool compare(interval &x, interval &y) {
	return ((x.value != y.value) ? (x.left < y.left) : ((x.value & 1) ? (x.right < y.right) : (x.right > y.right)));
}

int discret (int x) {
  return lower_bound (arr2 + 1, arr2 + len2 + 1, x) - arr2 - 1;
}
void add (int now) {
  cnt1[++cnt2[arr1[now]]]++;
  all = max (all, cnt2[arr1[now]]);
}
void del (int now) {
  if (cnt1[cnt2[arr1[now]]] == 1 && cnt2[arr1[now]] == all) {
    all--;
  }
  cnt1[cnt2[arr1[now]]--]--;
}

int main () {
  // ios :: sync_with_stdio (false);
  // cin.tie (0), cout.tie (0);

  // freopen ("std.in", "r", stdin);
  // freopen ("std.out", "w", stdout);

  // cin >> n >> m;
  scanf ("%d %d", &n, &m);
  len1 = sqrt (n);
  for (int i = 1; i <= n; ++i) {
    // cin >> arr1[i];
    scanf ("%d", &arr1[i]);
    arr2[i] = arr1[i];
  }
  sort (arr2 + 1, arr2 + n + 1);
  len2 = unique (arr2 + 1, arr2 + n + 1) - arr2 - 1;
  for (int i = 1; i <= n; ++i) {
    arr1[i] = discret (arr1[i]);
  }

  for (int i = 1; i <= m; ++i) {
    inter[i].identity = i;
    // cin >> inter[i].left >> inter[i].right;
    scanf ("%d %d", &inter[i].left, &inter[i].right);
    inter[i].value = (inter[i].left - 1) / len1;
  }
  sort (inter + 1, inter + m + 1, compare);

  int left_ = 1, right_ = 0;
  for (int i = 1; i <= m; ++i) {
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
    ans[inter[i].identity] = all;
  }
  
  for (int i = 1; i <= m; ++i) {
    // cout << '-' << ans[i] << '\n';
    printf ("%d\n", ans[i]);
  }
  // fclose (stdin);
  // fclose (stdout);

  return 0;
}