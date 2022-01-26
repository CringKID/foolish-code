#include <bits/stdc++.h>
using namespace std;
struct node {
  int x, y;
};
int n, m, mp[101][101], dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0}, ans;

void bfs(int x, int y) {
  mp[x][y] = 1;
  queue<node> q;
  node p;
  p.x = x;
  p.y = y;
  q.push(p);
  while (!q.empty()) {
    node t = q.front();
    q.pop();
    for (int i = 0; i <= 3; i++) {
      int xx = t.x + dx[i];
      int yy = t.y + dy[i];
      if (xx >= 1 && xx <= n && yy >= 1 && yy <= m && mp[xx][yy] == 0) {
        mp[xx][yy] = 1;
        node nn;
        nn.x = xx;
        nn.y = yy;
        q.push(nn);
      }
    }
  }
  return;
}
int main() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      char c;
      cin >> c;
      if (c == '0') {
        mp[i][j] = 1;
      }
    }
  }

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (mp[i][j] == 0) {
        ans++;
        bfs(i, j);
      }
    }
  }
  cout << ans;
}