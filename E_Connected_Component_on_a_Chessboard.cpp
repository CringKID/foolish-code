#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;
using Pii = pair <int, int>;
using Pll = pair <ll, ll>;
const int kMaxN = 1e5 + 5, kMod = 1e9 + 7, kInf = 1e9;

int q, b, w, dx, dy, cur;
//#define contest
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);
#ifdef contest
  freopen (, , stdin);
  freopen (, , stdout);
#endif

  cin >> q;
  while (q--) {
    cin >> b >> w;
    if (b > 3 * w + 1 || w > 3 * b + 1) {
      cout << "NO" << '\n';
      continue;
    }
    cout << "YES" << '\n';
    (w >= b ? (dx = dy = cur = 2) : (dx = 2, dy = cur = 3));
    while (w || b) {
      if ((dx + dy) & 1) {
        if (!b) { dy--; break; }
        b--;
      } else {
        if (!w) { dy--; break; }
        w--;
      }
      cout << dx << ' ' << dy << '\n';
      dy++;
    }
    for (int i = cur; i <= dy; i++) {
      if (((dx + i) & 1) && w) {
        cout << dx - 1 << ' ' << i << '\n';
        if (--w) { 
          cout << dx + 1 << ' ' << i << '\n', w--; 
        }
      }
      if (!((dx + i) & 1) && b) {
        cout << dx - 1 << ' ' << i << '\n';
        if (--b) {
          cout << dx + 1 << ' ' << i << '\n', b--;
        }
      }
    }
    if (b || w) {
      cout << dx << ' ' << dy + 1 << '\n';
    }
  }
  return 0;
}