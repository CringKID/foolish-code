#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;
using Pii = pair <int, int>;
using Pll = pair <ll, ll>;
const int kMaxN = 1e5 + 5, kMod = 1e9 + 7, kInf = 1e9;

ll T, n, a, b, flag = 1, cnt = 1;
//#define contest
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);
#ifdef contest
  freopen (, , stdin);
  freopen (, , stdout);
#endif

  cin >> T;
  while (T--) {
    cin >> n >> a >> b, flag = 1, cnt = 1;
    if (n != 1) {
      if (a != 1) {
        while (cnt <= n) {
          if (!((n - cnt) % b)) {
            flag = 0; 
            break;
          }
          cnt = cnt * a;
        }
        cout << (flag ? "No" : "Yes") << '\n';
      } else {
        cout << ((n - 1) % b ? "No" : "Yes") << '\n';
      }
    } else {
      cout << "Yes" << '\n';
    }
  }
  return 0;
}