#include <bits/stdc++.h>

using namespace std;
const int kMaxN = 1e5 + 5;

char ch1[kMaxN], ch2[kMaxN];
int len, cnt1, cnt2;
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> ch1 >> ch2;
  len = strlen (ch2);
  for (int i = 0; i < len; i++) {
    if (ch1[i] == '4' && ch2[i] == '7') {
      cnt1++;
    } else if (ch1[i] == '7' && ch2[i] == '4') {
      cnt2++;
    }
  }
  cout << max (cnt1, cnt2) << '\n';
  return 0;
}