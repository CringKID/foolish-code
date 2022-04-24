#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;
using ull = unsigned long long;
using Pii = pair <int, int>;
using Pll = pair <ull, ull>;
const int kMaxN = 155, kMod = 1e9 + 7, kInf = 1e9;

ull arr[kMaxN], sum[kMaxN], n;
void solve (ull x) {
  for (int i = 50; i >= 0; i--) {
    if (x / ull (pow (2, i))) {
      if (!sum[i]) {
        sum[i] = x;
        break;
      } else {
        x ^= sum[i];
      }
    }
  }
}
//#define contest
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);
#ifdef contest
  freopen (, , stdin);
  freopen (, , stdout);
#endif

  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> arr[i], solve (arr[i]);
  }
  ull ans = 0;
  for (int i = 50; i >= 0; i--) {
    if ((ans ^ sum[i]) > ans) {
      ans ^= sum[i];
    }
  }
  cout << ans << '\n';
  return 0;
} 