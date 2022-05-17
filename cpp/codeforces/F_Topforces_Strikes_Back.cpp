#include <iostream>
#include <algorithm>
#include <set>

using namespace std;
using ll = long long;
using Pii = pair <int, int>;
using Pll = pair <ll, ll>;
const int kMaxN = 2e5 + 5, kMod = 1e9 + 7, kInf = 1e9;

set <int> Set;
int arr[kMaxN], tot, ans;
//#define contest
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);
#ifdef contest
  freopen (, , stdin);
  freopen (, , stdout);
#endif

  int T; cin >> T;
  while (T--) {
    int n, ans = 0; tot = 0;
    cin >> n;
    for (int i = 1; i <= n; i++) {
      int x; cin >> x, Set.insert (x);
    }
    for (int i : Set) {
      arr[++tot] = i;
    }
    Set.clear ();
    for (int i = tot; i >= 1; i--) {
      ans = max (ans, arr[i]);
      for (int j = tot; j > i; j--) {
        if (arr[j] % arr[i] != 0) {
          ans = max (ans, arr[i] + arr[j]);
          for (int k = j - 1; k > i; k--) {
            if (arr[j] % arr[k] != 0 && arr[k] % arr[i] != 0) {
              ans = max (ans, arr[i] + arr[j] + arr[k]);
              break;
            }
          }
          break;
        }
      }
    }
    cout << ans << '\n';
  }
  return 0;
}