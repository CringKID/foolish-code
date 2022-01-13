#include <bits/stdc++.h>

using namespace std;
using ll = long long;

vector <pair <int, int> > solve (int h, int w, int a, int b) {
  vector <pair <int, int> > ans;
  if (w == 2) {
    for (int i = 1; i < a; i++) {
      ans.emplace_back (i, 1), ans.emplace_back (i, 2);
    }
    for (int i = a; i <= h; i++) {
      ans.emplace_back (i, b ^ 3);
    }
    for (int i = h; i >= a; i--) {
      ans.emplace_back (i, b);
    }
  } else if (h > 2 && (a > 2 || a == 2 && b != w)) {
    for (int i = 1; i <= w; i++) {
      ans.emplace_back (1, i);
    }
    for (pair <int, int> P : solve (h - 1, w, a - 1, w + 1 - b)) {
      ans.emplace_back (P.first + 1, w + 1 - P.second);
    }
  } else {
    ans = solve (w, h, b, a);
    for (pair <int, int> P : ans) {
      swap (P.first, P.second);
    }
  }
  return ans;
}

int h, w, a, b;
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> h >> w >> a >> b;
  for (pair <int, int> P : solve (h, w, a, b)) {
    cout << P.first << ' ' << P.second << '\n';
  }
  return 0;
}