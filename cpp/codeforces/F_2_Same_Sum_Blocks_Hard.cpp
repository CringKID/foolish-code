#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
const int kMaxN = 1505;

struct Node {
  int l, r;
}; vector <Node> node[kMaxN * kMaxN];
int arr1[kMaxN], arr2[kMaxN * kMaxN], n, x, siz, num, ans, idx, p;
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> x;
    arr1[i] = arr1[i - 1] + x;
  }
  for (int i = 1; i <= n; i++) {
    for (int j = i; j <= n; j++) {
      int diff = arr1[j] - arr1[i - 1];
      arr2[++siz] = diff;
    }
  }
  sort (arr2 + 1, arr2 + siz + 1), siz = unique (arr2 + 1, arr2 + siz + 1) - arr2 - 1;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= i; j++) {
      int diff = arr1[i] - arr1[j - 1], cur = lower_bound (arr2 + 1, arr2 + siz + 1, diff) - arr2;
      node[cur].push_back ({j, i});
    }
  }
  for (int i = 1; i <= siz; i++) {
    int p = 0, num = 0;
    for (int j = 0; j < node[i].size (); j++) {
      if (node[i][j].l > p) {
        num++, p = node[i][j].r;
      }
    }
    if (num > ans) {
      ans = num, idx = i;
    }
  }
  cout << ans << '\n';
  for (int i = 0; i < node[idx].size (); i++) {
    if (node[idx][i].l > p) {
      cout << node[idx][i].l << ' ' << node[idx][i].r << '\n';
      p = node[idx][i].r;
    }
  }
  return 0;
}