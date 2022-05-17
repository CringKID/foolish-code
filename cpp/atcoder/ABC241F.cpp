#include <iostream>
#include <algorithm>
#include <queue>
#include <map>
#include <set>

using namespace std;
using ll = long long;
using Pii = pair <int, int>;

queue <Pii> que;
map <Pii, int> dist;
map <int, set <int> > row, col;
int h, w, n, sx, sy, ex, ey;
void move (int x, int y, int step) {
  if (x < 1 || x > h || y < 1 || y > w || dist.count ({x, y})) {
    return ;
  }
  que.push ({x, y}), dist[{x, y}] = step;
}
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> h >> w >> n >> sx >> sy >> ex >> ey;
  for (int i = 1, x, y; i <= n; i++) {
    cin >> x >> y, row[x].insert (y), col[y].insert (x);
  }
  dist[{sx, sy}] = 0, que.push ({sx, sy});
  while (!que.empty ()) {
    Pii p = que.front (); que.pop ();
    if (p.first == ex && p.second == ey) {
      cout << dist[{ex, ey}] << '\n';
      return 0;
    }
    if (row.count (p.first)) {
      auto from = row[p.first].lower_bound (p.second);
      from != row[p.first].end () ? move (p.first, *from - 1, dist[p] + 1) : void ();
      from != row[p.first].begin () ? (from--, move (p.first, *from + 1, dist[p] + 1)) : void ();
    }
    if (col.count (p.second)) {
      auto from = col[p.second].lower_bound (p.first);
      from != col[p.second].end () ? move (*from - 1, p.second, dist[p] + 1) : void ();
      from != col[p.second].begin () ? (from--, move (*from + 1, p.second, dist[p] + 1)) : void ();
    }
  }
  cout << -1 << '\n';
  return 0;
}