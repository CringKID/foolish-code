#include <bits/stdc++.h>

using namespace std;
using ll = long long;
const int kMaxN = 2e5 + 5;

int arr[kMaxN], sum[kMaxN], n, m;
ll ans1, ans2;
class TreeArray {
private :
  int tree[kMaxN << 1], size;
  int lowbit (int sum) {
    return sum & -sum;
  }
public : 
  void init (int n) {
    size = n;
    fill (tree + 1, tree + size + 1, 0);
  }
  
  void update (int now) {
    for (int i = now; i <= size; i += lowbit (i)) {
      tree[i]++;
    }
  }
  int query (int now) {
    int tot = 0;
    for (int i = now; i > 0; i -= lowbit (i)) {
      tot += tree[i];
    }
    return tot;
  }
} tree;

int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> arr[i];
  }

  for (int i = 1; i <= n; i++) {
    sum[i] = (arr[i] <= m ? 1 : -1) + sum[i - 1];
  }
  tree.init (n << 1 | 1);
  tree.update (n + 1);
  for (int i = 1; i <= n; i++) {
    ans1 += tree.query (sum[i] + n + 1);
    tree.update (sum[i] + n + 1);
  }

  for (int i = 1; i <= n; i++) {
    sum[i] = (arr[i] < m ? 1 : -1) + sum[i - 1];
  }
  tree.init (n << 1 | 1);
  tree.update (n + 1);
  for (int i = 1; i <= n; i++) {
    ans2 += tree.query (sum[i] + n + 1);
    tree.update (sum[i] + n + 1);
  }

  cout << ans1 - ans2 << '\n';
  return 0;
}