#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
using ll = long long;
using Pii = pair <int, int>;
using Pll = pair <ll, ll>;
const int kMaxN = 1e5 + 5, kMod = 1e9 + 7, kInf = 1e9;

char ch1[kMaxN], ch2[kMaxN];
int k, cnt, cnt4, cnt7;
//#define contest
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);
#ifdef contest
  freopen (, , stdin);
  freopen (, , stdout);
#endif

  memset (ch1, 0, sizeof (ch1)), memset (ch2, 0, sizeof (ch2));
  gets (ch1), gets (ch2), k = strlen (ch1);
  for (int i = 0; i < k; i++) {
    if (ch1[i] == ch2[i]) {
      continue;
    } else {
      if (ch2[i] == '7') {
        cnt7++;
      } else {
        cnt4++;
      }
    }
  }
  cout << (cnt4 <= cnt7 ? cnt7 : cnt4) << '\n';
  return 0;
}