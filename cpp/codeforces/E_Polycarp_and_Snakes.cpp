#include <iostream>
#include <algorithm>

using namespace std;
const int kMaxN = 2e3 + 5;

char ch[kMaxN][kMaxN];
int t, n, m, l[kMaxN], r[kMaxN], sum[kMaxN], arr[kMaxN];
int calc (int c) {
  int cnt = 0;
  for (int i = arr[c]; i <= sum[c]; i++) {
    for (int j = l[c]; j <= r[c]; j++) {
      (ch[i][j] == '*' || ch[i][j] == c) ? cnt++ : 0;
      ch[i][j] = '*';
    }
  }
  return cnt;
}
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> t;
  while (t--) {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
      cin >> ch[i] + 1;
    }
    for (int i = 'a'; i <= 'z'; i++) {
      l[i] = arr[i] = 1e9, r[i] = sum[i] = 0;
    }
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        if (ch[i][j] >= 'a' && ch[i][j] <= 'z') {
          l[ch[i][j]] = min (l[ch[i][j]], j), r[ch[i][j]] = max (r[ch[i][j]], j);
          arr[ch[i][j]] = min (arr[ch[i][j]], i), sum[ch[i][j]] = max (sum[ch[i][j]], i);
        }
      }
    }
    int cnt = 0; bool tag = true;
    for (int i = 'z'; i >= 'a'; i--) {
      if (!sum[i]) {
        continue;
      }
      (sum[i] != arr[i] && l[i] != r[i]) ? tag = false : 0;
      (calc(i) != (r[i] - l[i] + 1) * (sum[i] - arr[i] + 1)) ? tag = false : 0;
    }
    if (tag == false) {
      cout << "NO" << '\n';
      continue;
    }
    cout << "YES" << '\n';
    for (int i = 'a'; i <= 'z'; i++) {
      sum[i] ? cnt = i - 'a' + 1 : 0;
    }
    cout << cnt << endl;
    for (int i = 'y'; i >= 'a'; i--) {
      if (!sum[i]) {
        arr[i] = arr[i + 1], sum[i] = sum[i + 1];
        l[i] = l[i + 1], r[i] = r[i + 1];
      }
    }
    for (int i = 'a'; i <= 'z'; i++) {
      if (sum[i]) {
        cout << arr[i] << ' ' << l[i] << ' ' << sum[i] << ' ' << r[i] << '\n';
      }
    }
  }
  return 0;
}