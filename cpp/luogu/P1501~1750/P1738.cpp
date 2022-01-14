#include <bits/stdc++.h>
using namespace std;
int n;
set<string> s;
string t;
int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    cin >> t;
    string x = "";
    for (auto j : t) {
      if (j == '/') s.insert(x);
      x += j;
    }
    s.insert(x);
    printf("%d\n", s.size() - 1);
  }
  return 0;
}