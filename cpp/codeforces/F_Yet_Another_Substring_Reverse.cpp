#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
const int kN = 21;

string str;
int dp[1 << kN], n, st[kN], rec;
int main () {
  cin >> str;
  for (int i = 0, tmp, cnt; i < str.size (); i++) {
    tmp = cnt = 0;
    memset (st, 0, sizeof (st));
    for (int j = i; j < str.size (); j++) {
      if (st[str[j] - 'a']) {
        break;
      }
      tmp += 1 << (str[j] - 'a');
      st[str[j] - 'a'] = 1, cnt++, dp[tmp] = cnt;
    }
  }
  for (int i = 0; i < 1 << 20; i++) {
    for (int j = 0; j < 20; j++) {
      i >> j & 1 ? dp[i] = max (dp[i], dp[i ^ (1 << j)]) : 0;
    }
  }
  for (int i = 0; i < 1 << 20; i++) {
    rec = max (rec, dp[i] + dp[i ^ ((1 << 20) - 1)]);
  }
  cout << rec << '\n';
  return 0;
}