#include <iostream>
#include <algorithm>
#include <deque>

using namespace std;
const int kMaxN = 555, kDir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

struct Node {
  int x, y, step;
};
char Map[kMaxN][kMaxN];
int n, m, vis[kMaxN][kMaxN];
int BFS () {
  deque <Node> dq; dq.push_front ({1, 1, 0});
  while (!dq.empty ()) {
    Node t = dq.front (); dq.pop_front ();
    int x = t.x, y = t.y, step = t.step;
    if (vis[x][y]) {
      continue;
    }
    vis[x][y] = 1;
    if (x == n && y == m) {
      return step;
    }
    for (int k = 0; k < 4; k++) {
      int xx = x + kDir[k][0], yy = y + kDir[k][1];
      if (xx >= 1 && xx <= n && yy >= 1 && yy <= m && !vis[xx][yy]) {
        if (Map[xx][yy] == '.') {
          dq.push_front ({xx, yy, step});
        } else {
          for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
              int n_x = xx + i, n_y = yy + j;
              if (n_x >= 1 && n_x <= n && n_y >= 1 && n_y <= m && !vis[n_x][n_y]) {
                dq.push_back ({n_x, n_y, step + 1});
              }
            }
          }
        }
      }
    }
  }
  return -1;
}
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> Map[i] + 1;
  }
  cout << BFS () << '\n';
  return 0;
}