#include <iostream>
#include <algorithm>
#include <cstring>
#include <cctype>
#include <set>

using namespace std;
const int kMaxN = 5e4 + 5;

struct Node {
  int l, r;
  mutable char val;
  Node (int _l, int _r = -1, char _val = 0) : l (_l), r (_r), val (_val) {
  }
  bool operator < (const Node& an) const {
    return l < an.l;
  } 
};
using itr = set <Node> :: iterator;
set <Node> odt;
itr split (int x) {
  itr it = odt.lower_bound (Node (x));
  if (it != odt.end () && it -> l == x) {
    return it;
  }
  --it;
  int l = it -> l, r = it -> r;
  char val = it -> val;
  odt.erase (it), odt.insert (Node (l, x - 1, val));
  return odt.insert (Node (x, r, val)).first;
}
int calc (int l, int r, char val) {
  itr itR = split (r + 1), itL = split (l);
  int ans = 0;
  for ( ; itL != itR; ++itL) {
    if (itL -> val == val) {
      ans += itL -> r - itL -> l + 1;
    }
  }
  return ans;
}
void assign (int l, int r, char val) {
  itr itR = split (r + 1), itL = split (l);
  odt.erase (itL, itR);
  odt.insert (Node (l, r, val));
}
void Sort (int l, int r) {
  int cnt[27];
  memset (cnt, 0, sizeof (cnt));
  itr itR = split (r + 1), itL = split (l), it = itL;
  for ( ; itL != itR; ++itL) {
    cnt [itL -> val - 'A'] += itL -> r - itL -> l + 1;
  }
  odt.erase (it, itR);
  for (int i = 0; i < 26; ++i) {
    if (cnt[i]) {
      odt.insert (Node (l, l + cnt[i] - 1, i + 'A'));
      l += cnt[i];
    }
  }
}
int n, m, cnt = 1, opt, l, r;
char str[kMaxN], pre, dict[2];
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n >> m >> (str + 1), pre = toupper (str[1]);
  if (n == 50000 && m == 50000) {
    
  }
  for (int i = 2; i <= n; i++) {
    str[i] = toupper (str[i]);
    if (str[i] == pre) {
      cnt++;
    } else {
      odt.insert (Node (i - cnt, i - 1, pre)), cnt = 1, pre = str[i];
    }
  }
  odt.insert (Node (n + 1 - cnt, n, pre));
  while (m--) {
    cin >> opt >> l >> r;
    if (opt == 1) {
      cin >> dict;
      cout << calc (l, r, toupper (dict[0])) << '\n';
    } else if (opt == 2) {
      cin >> dict;
      assign (l, r, toupper (dict[0]));
    } else {
      Sort (l, r);
    }
  }
  return 0;
}