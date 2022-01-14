#include <iostream>
#include <algorithm>
#include <set>

using namespace std;
using ll = long long;
using Pii = pair <int, int>;
using Pll = pair <ll, ll>;
const int kMaxN = 1e5 + 5, kMod = 1e9 + 7, kInf = 1e9;

struct Node {
  int left, right;
  mutable int value;
  Node (int left_, int right_, int value_) : left (left_), right (right_), value (value_) {
  }
  Node () {
  }
  bool operator < (const Node & another) const {
    return left < another.left;
  }
} ;
set <Node> odt;
int n, q, ans, opt, Left, Right;

auto split (int cur) {
  auto iter = odt.lower_bound (Node (cur, cur, 0));
  if (iter != odt.end () && iter -> left == cur) {
    return iter;
  }
  iter--;
  int left = iter -> left, right = iter -> right, value = iter -> value;
  odt.erase (iter);
  odt.emplace (left, cur - 1, value);
  return odt.emplace (cur, right, value).first;
}
void assign (int left, int right, int value) {
  auto itright = split (right + 1), itleft = split (left);
  for (auto iter = itleft; iter != itright; iter++) {
    ans -= iter -> value * (iter -> right - iter -> left + 1);
  }
  ans += (right - left + 1) * value;
  odt.erase (itleft, itright);
  odt.emplace (left, right, value);
}

int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n >> q, ans = n;
  odt.emplace (1, n, 1);
  while (q--) {
    cin >> Left >> Right >> opt;
    assign (Left, Right, opt - 1);
    cout << ans << '\n';
  }
  return 0;
}