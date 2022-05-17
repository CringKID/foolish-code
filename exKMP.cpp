#include <iostream>
#include <algorithm>

using namespace std;
const int kMaxN = 2e7 + 5;
string s1, s2;
int l1, l2, nxt[kMaxN], f[kMaxN];
void Next (int arr[], string s) {
  for (int i = 1, j; i < s2.size (); i++) {
    if (j + arr[j] > i) {
      arr[i] = min (nxt[j - i], j + arr[j] - i);
    }
    for ( ; i + arr[i] < s2.size () && s[arr[i]] == s2[i + arr[i]]; arr[i]++) {
    }
    if (i + arr[i] > j + arr[j]) {
      j = i;
    }
  }
}
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> s1 >> s2, l1 = s1.size (), l2 = s2.size ();
  Next (nxt, s2), Next (f, s1);
  return 0;
}