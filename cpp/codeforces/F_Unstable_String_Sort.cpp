#include <iostream>
#include <algorithm>

using namespace std;
const int kMaxN = 2e5 + 5;

int n, k, p[kMaxN], q[kMaxN], rec[kMaxN], arr[kMaxN], ans[kMaxN];
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n >> k;
  for_each (p + 1, p + n + 1, [&] (int &x) { cin >> x; });
  for_each (q + 1, q + n + 1, [&] (int &x) { cin >> x; });
  for (int i = 1; i <= n; i++) {
    rec[p[i]] = i;
  }
  for (int i = 1; i < n; i++) {
    rec[q[i + 1]] < rec[q[i]] ? (arr[rec[q[i]]]--, arr[rec[q[i + 1]]]++) : 0;
  }
  for (int i = 1, cur = 0; i <= n; i++) {
    cur ? ans[i] = ans[i - 1] : ans[i] = ans[i - 1] + 1;
    cur += arr[i];
  }
  if (ans[n] < k) {
    cout << "NO" << '\n';
    return 0;
  }
  cout << "YES" << '\n';
  for (int i = 1; i <= n; i++) {
    cout << char (min (ans[rec[i]], k) + 'a' - 1);  
  }
  cout << '\n';
  return 0;
}