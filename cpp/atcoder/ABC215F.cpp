#include <iostream>
#include <algorithm>

using namespace std;
const int kMaxN = 2e5 + 5;

struct Node {
  int x, y;
} node[kMaxN];
int n, mmax[kMaxN], mmin[kMaxN];
bool judge (int x) {
  for (int i = 1, j = 1; i <= n && j <= n; (node[i].x - node[j].x >= x ? j++ : i++)) {
    if (node[i].x - node[j].x >= x && (mmax[i] - node[j].y >= x || node[j].y - mmin[i] >= x)) {
      return true;
    }
  }
  return false;
}
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> node[i].x >> node[i].y;
  }
  sort (node + 1, node + n + 1, [] (Node n1, Node n2) { return n1.x == n2.x ? n1.y < n2.y : n1.x < n2.x; });
  fill (mmax, mmax + n + 1, -1), fill (mmin, mmin + n + 1, int (1e9));
  mmax[n] = mmin[n] = node[n].y;
  for (int i = n - 1; i >= 1; i--) {
    mmax[i] = max (mmax[i + 1], node[i].y);
    mmin[i] = min (mmin[i + 1], node[i].y);
  }
  int l = 0, r = 1e9;
  while (l <= r) {
    int mid = l + r >> 1;
    judge (mid) ? l = mid + 1 : r = mid - 1;
  }
  cout << l - 1 << '\n';
  return 0;
}