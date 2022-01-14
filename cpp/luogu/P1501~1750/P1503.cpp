#include <bits/stdc++.h>

using namespace std;

const int kMaxN = 5e4 + 5;

int arr[kMaxN], tail, n, m;
set<int> sset;
set<int>::iterator iter;

int main() {
  ios ::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);

  cin >> n >> m;
  sset.insert(0);
  sset.insert(n + 1);

  for (int i = 1; i <= m; i++) {
    char ch;
    cin >> ch;
    if (ch == 'D') {
      int x;
      cin >> x;
      sset.insert(x);
      arr[++tail] = x;
    } else if (ch == 'Q') {
      int x;
      cin >> x;
      iter = sset.lower_bound(x);
      if (*iter == x) {
        cout << 0 << '\n';
        continue;
      }
      int ans = *iter - *(--iter);
      cout << ans - 1 << '\n';
    } else {
      iter = sset.find(arr[tail--]);
      sset.erase(iter);
    }
  }
  return 0;
}