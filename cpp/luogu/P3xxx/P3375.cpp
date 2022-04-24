#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;
using Pii = pair <int, int>;
using Pll = pair <ll, ll>;
const int kMaxN = 1e6 + 5, kMod = 1e9 + 7, kInf = 1e9;

string str1, str2;
int l1, l2, nxt[kMaxN];
void solvenxt () {
  for (int i = 1, l; i <= l2; i++) {
    for (l = nxt[i]; l && str2[l] != str2[i]; l = nxt[l]) {
    }
    nxt[i + 1] = l + (str2[l] == str2[i]);
  }
}
void solveans () {
  for (int i = -1, j = -1; i < l1 - l2; ) {
    for ( ; j - i < l2 && str1[j + 1] == str2[j - i]; j++) {
    }
    if (j - i == l2) {
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

  cin >> str1 >> str2;
  l1 = str1.length (), l2 = str2.length ();
  solvenxt (), solveans ();
  for (int i = 1; i <= l2; i++) {
    cout << nxt[i] << ' ';
  }
  return 0;
}