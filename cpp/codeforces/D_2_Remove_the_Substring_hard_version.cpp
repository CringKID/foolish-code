#include <iostream>
#include <algorithm>

using namespace std;
const int kMaxN = 2e5 + 5;

string str1, str2;
int lft[kMaxN], rght[kMaxN], l1, l2, i, j, ans;
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> str1 >> str2, l1 = str1.size (), l2 = str2.size ();
  if (l1 == l2) {
    cout << 0 << '\n';
  } else {
    for (i = j = 0; i < l2; (str1[j] == str2[i] ? (lft[i] = j, i++) : 0), j++) {
    }
    for (i = l2 - 1, j = l1 - 1; i > -1; (str1[j] == str2[i] ? (rght[i] = j, i--) : 0), j--) {
    }
    ans = max (rght[0], l1 - lft[l2 - 1] - 1);
    for (i = 0; i < l2 - 1; ans = max (ans, rght[i + 1] - lft[i] - 1), i++) {
    }
    cout << ans << '\n';
  }
  return 0;
}