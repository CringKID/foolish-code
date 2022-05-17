#include <iostream>
#include <algorithm>
#include <map>

using namespace std;
using ll = long long;
const ll kMaxN = 2e5 + 5, kInf = 3e18;

map <int, int> Map;
ll arr[kMaxN], n, k, sum[kMaxN], ans = kInf;
ll check (int x, int opt) {
  ll res = 0, index, num = Map[x];
  index = (opt == 1 ? upper_bound (arr + 1, arr + n + 1, x) : lower_bound (arr + 1, arr + n + 1, x)) - arr - (opt == 2 ? 1 : 0);
  res += (opt == 1 ? ((sum[n] - sum[index - 1]) - (n - index + 1) * (x + 1)) : (index * (x - 1) - sum[index]));
  res += min (k - num, (opt == 1 ? n - index + 1 : index)), num += min (k - num, (opt == 1 ? n - index + 1 : index));
  if (num < k) {
    index = opt == 1 ? (lower_bound (arr + 1, arr + n + 1, x) - arr - 1) : upper_bound (arr + 1, arr + n + 1, x) - arr;
    res += (opt == 1 ? (index * (x - 1) - sum[index]) : ((sum[n] - sum[index - 1]) - (n - index + 1) * (x + 1)));
    res += k - num;
  }
  return res;
}
int main () {
  ios :: sync_with_stdio(false);
  cin.tie (0), cout.tie (0);

  cin >> n >> k;
  for (int i = 1; i <= n; i++) {
    cin >> arr[i], Map[arr[i]]++;
    if (Map[arr[i]] >= k) {
      cout << 0 << '\n';
      return 0;
    }
  }
  sort (arr + 1, arr + 1 + n);
  for (int i = 1; i <= n; i++) {
    sum[i] = sum[i - 1] + arr[i];
  }
  for (int i = 1; i <= n; i++) {
    ans = min (ans, min (check (arr[i], 1), check (arr[i], 2)));
  }
  cout << ans << '\n';
  return 0;
}