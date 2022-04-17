#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
using ll = long long;
using Pii = pair <int, int>;
using Pll = pair <ll, ll>;
const int kMaxM = 1 << 17, kMod = 1e9 + 7, kInf = 1e9;

ll rec;
Pii P[kMaxM];
int n, val, m, arr[25];
//#define contest
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);
#ifdef contest
  freopen (, , stdin);
  freopen (, , stdout);
#endif

  cin >> n, m = 1 << n;
  for (int i = 1; i < m; i++) {
    cin >> val;
    P[i] = {val, i};
  }
  sort (P + 1, P + m);
  for (int i = 1; i < m; i++) {
    int cur = P[i].second;
    for (int j = n; j >= 0; j--) {
      if (!((cur >> j) & 1)) {
        continue;
      }
      if (!arr[j]) {
        arr[j] = cur, rec += P[i].first;
        break;
      } else {
        cur ^= arr[j];
      }
    }
  }
  cout << rec << '\n';
  return 0;
}