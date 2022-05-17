#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;
using Pii = pair <int, int>;
using Pll = pair <ll, ll>;
const int kMaxN = 1e6 + 5, kMod = 1e9 + 7, kInf = 1e9;

int l1, l2;
string s1, s2;
int nxt[kMaxN];
void Next () {
  for (int i = 1, l; i < l2; i++) {
    for (l = nxt[i]; l && s2[l] != s2[i]; l = nxt[l]) {
    }
    nxt[i + 1] = l + s2[l] == s2[i];
  }
}
void calcval () {
  for (int i = -1, j = -1; i < l1 - l2; ) {
    for ( ; j - i < l2 && s1[j + 1] == s2[j - i]; j++) {
    }
    if (j - i == l2) {      // all cmp
      cout << i + 2 << '\n';
    }
    i = i == j ? ++j : j - nxt[j - i];
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

  cin >> s1 >> s2, l1 = s1.size (), l2 = s2.size ();
  Next (), calcval ();
  for (int i = 1; i <= l2; i++) {
    cout << nxt[i] << ' ';
  }
  return 0;
}