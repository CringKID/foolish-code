#include <bits/stdc++.h>

using namespace std;
const int kMaxN = 1e4 + 5;
const string cstr[3] = {"aabb", "abab", "abba"};

int k, n, m, head[kMaxN], arr[3];
char ch[4][kMaxN];
bool Judge (int p1, int p2) {
  int sum = m, lft = strlen (ch[p1] + 1), rght = strlen (ch[p2] + 1);
  for (int cur; lft && rght; lft--, rght--) {
    if (ch[p1][lft] != ch[p2][rght]) {
      return false;
    } else if (head[ch[p1][lft]] && (!(--sum))) {
      return true;
    } 
  }
  return false;
}

int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  head['a'] = head['e'] = head['i'] = head['o'] = head['u'] = 1;
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j <= 3; j++) {
      cin >> ch[j] + 1;
    }
    if (Judge (0, 1) && Judge (1, 2) && Judge (2, 3)) {
      arr[0]++, arr[1]++, arr[2]++;
    } else {
      if (Judge (0, 1) && Judge (2, 3)) {
        arr[0]++;
      }
      if (Judge (0, 2) && Judge (1, 3)) {
        arr[1]++;
      }
      if (Judge (0, 3) && Judge (1, 2)) {
        arr[2]++;
      }
    }
  }

  bool tag = false;
  for (int i = 0; i < 3; i++) {
    if (arr[i] != n) {
      tag = true;
    }
  }
  if (!tag) {
    cout << "aaaa" << '\n';
  } else {
    for (int i = 0; i < 3; i++) {
      if (arr[i] == n) {
        cout << cstr[i] << '\n';
        return 0;
      }
    }
    cout << "NO" << '\n';
  }
  return 0;
}