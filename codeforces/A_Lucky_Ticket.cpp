#include <bits/stdc++.h>

using namespace std;
const int kMaxN = 1e5 + 5;

char ch[kMaxN], fake[kMaxN];
int len, sum;
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> fake >> ch;
  len = strlen (ch);
  bool ans = true;
  for (int i = 1; i < len; i++) {
    if (ch[i] != '4' && ch[i] != '7') {
      ans = false;
    }
  }
  for (int i = 0; i < len; i++) {
    if (i < len / 2) {
      sum += ch[i] - '0';
    } else {
      sum -= ch[i] - '0';
    }
  }
  if (sum != 0) {
    ans = false;
  }
  cout << (ans ? "YES" : "NO") << '\n';
  return 0;
}