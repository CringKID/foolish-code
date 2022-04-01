#include <iostream>
#include <algorithm>
#include <stack>

using namespace std;
const int kMaxN = 5e5 + 5;

struct Node {
  int x, p, k, id;
} node[kMaxN << 1];
int n, q, a[kMaxN], b[kMaxN], p[kMaxN], tree[kMaxN], ans[kMaxN];
stack <int> s;
void update (int x) {
  for (x++; x <= n; x += x & -x) {
    tree[x]++;
  }
}
int query (int x) {
  int cnt = 0;
  for (x++; x; x -= x & -x) {
    cnt += tree[x];
  }
  return cnt;
}
int main () {
  cin >> n >> q;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (int i = 1; i <= n; i++) {
    cin >> b[i];
  }
  for (int i = 1; i <= n; i++) {
    for ( ; !s.empty () && (a[s.top ()] == a[i] or b[i] >= b[s.top ()]); s.pop ()) {
    }
    if (!s.empty ()) {
      p[i] = s.top ();
    }
    s.push (i);
  }
  for (int i = 1, l, r; i <= q; i++) {
    cin >> l >> r;
    node[i] = {l - 1, l - 1, -1, i};
    node[i + q] = {r, l - 1, 1, i};
  }
  sort (node + 1, node + (q << 1 | 1), [] (Node a, Node b) { return a.x < b.x; });
  int j = 1;
  for ( ; !node[j].x; j++) {
  }
  for (int i = 1; i <= n; i++) {
    update (p[i]);
    for ( ; node[j].x == i and j <= (q << 1); j++) {
      ans[node[j].id] += node[j].k * query (node[j].p);
    }
  }
  for (int i = 1; i <= q; i++) {
    cout << ans[i] << '\n';
  }
  return 0;
}