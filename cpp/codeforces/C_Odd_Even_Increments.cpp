#include <iostream>
#include <algorithm>

using namespace std;
const int kMaxN = 55;

int n, m, t, arr1[kMaxN], arr2[kMaxN];
int main() {
  for (cin >> t; t; t--) {
    cin >> n; bool tag = false;
    for (int i = 1; i <= n; i++) {
      cin >> arr1[i], arr2[i] = ((arr1[i] & 1) ? 1 : 0);
    }
    for (int i = 1; i < n - 1; i++) {
      if (arr2[i] != arr2[i + 2]) {
        cout << "NO" << '\n', tag = true;
      }
    }
    if (!tag) {
      cout << "YES" << '\n';
    }
  }
  return 0;
}//https://zhuanlan.zhihu.com/p/502876766