#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;
const int kMaxN = 1e5 + 5;

char str[kMaxN];
ll Q, t, k;
ll DFS (ll x, ll cur) {
  if (!x) {
    return str[cur] - 'A';
  } else if (!cur) {
    return (str[0] - 'A' + x % 3) % 3;
  }
  return (DFS (x - 1, cur / 2) + ((cur & 1) ? 2 : 1)) % 3;
}
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  for (cin >> str >> Q; Q; Q--) {
    cin >> t >> k;
    cout << char (DFS (t, k - 1) + 'A') << '\n';
  }
  return 0;
}