#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
const int kMaxN = 2.5e4 + 5, me = 250, kMaxM = kMaxN * me;

int n, arr[kMaxM][2], tot, tr[kMaxN], ans, str[kMaxN];
vector <int> ve[kMaxM];
void update (int x, int val) {
  for (int i = x; i < kMaxN; tr[i] = max (tr[i], val), i += i & -i) {
  }
}
int query (int x) {
  int ans = 0;
  for (int i = x; i; ans = max (ans, tr[i]), i -= i & -i) {
  }
  return ans;
}
void DFS (int x, int y) {
  reverse (ve[x].begin (), ve[x].end ());
  for (int i = 0; i < int (ve[x].size ()); i++) {
    int to = ve[x][i];
    ans = max (ans, query (to - y) + 1), update (to, query (to - y) + 1);
  }
  for (int i = 0; i < 2; i++) {
    arr[x][i] ? DFS (arr[x][i], y + 1) : void ();
  }
}
int main () {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    char ch = getchar ();
    for ( ; ch != '0' && ch != '1'; ch = getchar ()) {
    }
    str[i] = ch - '0';
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 0, rec = 0; j < me && i + j <= n; j++) {
      (!arr[rec][str[i + j]]) ? arr[rec][str[i + j]] = ++tot : 0;
      rec = arr[rec][str[i + j]], ve[rec].push_back (i + j);
    }
  }
  DFS (0, 0);
  cout << ans << '\n';
  return 0;
}