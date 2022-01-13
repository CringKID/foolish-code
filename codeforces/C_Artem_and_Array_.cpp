#include <bits/stdc++.h>

using namespace std;
using ll = long long;
const int kMaxN = 5e5 + 5;

int n;
ll ans, arr[kMaxN];
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n >> arr[1] >> arr[2];
  for (int i = 3; i <= n; i++) {
    cin >> arr[i];
    while (arr[i - 1] <= arr[i - 2] && arr[i - 1] <= arr[i]) {
      ans += min (arr[i - 2], arr[i]), n--;
      arr[i - 1] = arr[i], i--;
    }
  }
  sort (arr + 1, arr + n + 1);
  for (int i = 1; i < n - 1; i++) {
    ans += arr[i];
  }
  cout << ans << '\n';
  return 0;
}