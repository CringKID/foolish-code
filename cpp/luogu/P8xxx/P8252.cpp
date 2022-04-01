#include <iostream>
#include <algorithm>

using namespace std;
const int kMaxN = 1e6 + 5;

int n, m, q, x, y, t, v, arr1[kMaxN], arr2[kMaxN << 1], rec[kMaxN], idx[kMaxN], sum[kMaxN];
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> q;
  while (q--) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> arr1[i];
      idx[i] = i, rec[i] = 0, sum[i] = sum[i - 1] + arr1[i];
      for (int j = 1; j <= arr1[i]; j++) {
        cin >> arr2[sum[i - 1] + j];
      }
    }
    sort (idx + 1, idx + n + 1, [] (int n1, int n2) { return arr1[n1] > arr1[n2]; });
    int i;
    for (int k = 1; k <= n; k++) {
      i = idx[k], x = y = 0;
      for (int j = 1; j <= arr1[i]; j++) {
        t = arr2[sum[i - 1] + j], v = rec[t], rec[t] = i;
        if (!v) {
          v = i;
        }
        if (!x) {
          x = v;
        } else if (x != v) {
          y = v;
        }
        if (x && y) {
          n = arr1[i] = -1;
        }
      }
    }
    if (~n) {
      cout << "NO" << '\n';
    } else {
      if (x == i || y == i) {
      } else if (arr1[x] > arr1[y]) {
        x = i;
      } else {
        y = i;
      }
      cout << "YES" << '\n' << x << ' ' << y << '\n';
    }
  }
  return 0;
}