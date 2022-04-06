#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 9005;
int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};
bool vis[maxn][maxn], vis2[maxn][maxn];
ll shi[maxn][maxn];
int n, m, k;
struct node {
  int x, y;
  ll h;
} e, s;
int bfs(int x, int y) {
  queue<node> q1, q2;
  int time = -1;
  if (shi[x][y] > 0) {
    q1.push({x, y, 0});
    vis[x][y] = 1;
  }
  while (!q1.empty()) {
    node cur = q1.front();
    q1.pop();
    if (cur.x == e.x && cur.y == e.y) {
      time = cur.h;
      break;
    }
    for (int i = 0; i < 4; i++) {
      int nx = cur.x + dx[i];
      int ny = cur.y + dy[i];
      if (1 <= nx && 1 <= ny && !vis[nx][ny] && cur.h + 1 < shi[nx][ny]) {
        vis[nx][ny] = 1;
        q1.push({nx, ny, cur.h + 1});
      }
    }
  }
  if (shi[e.x][e.y] > time && time >= 0) {
    q2.push({e.x, e.y, time});
    vis2[e.x][e.y] = 1;
  }
  while (!q2.empty()) {
    node cur = q2.front();
    q2.pop();
    if (shi[cur.x][cur.y] == 2e9) {
      return cur.h;
    }
    for (int i = 0; i < 4; i++) {
      int nx = cur.x + dx[i];
      int ny = cur.y + dy[i];
      if (1 <= nx && 1 <= ny && !vis2[nx][ny] && cur.h + 1 < shi[nx][ny]) {
        vis2[nx][ny] = 1;
        q2.push({nx, ny, cur.h + 1});
      }
    }
  }
  return -1;
}
int main() {
  bool xxx = 0, yyy = 0;
  cin >> n >> m >> k;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      shi[i][j] = 2e9;
      char ch;
      cin >> ch;
      if (ch == 'B') {
        vis2[i][j] = vis[i][j] = 1;
      } else if (ch == 'C') {
        s.x = i;
        s.y = j;
      } else if (ch == 'D') {
        e.x = i;
        e.y = j;
      }
    }
  }
  for (int i = 1; i <= k; i++) {
    int x, y;
    ll t;
    cin >> x >> y >> t;
    shi[x][y] = min(t, shi[x][y]);
    shi[x + 1][y] = min(t, shi[x + 1][y]);
    shi[x][y + 1] = min(t, shi[x][y + 1]);
    shi[x - 1][y] = min(t, shi[x - 1][y]);
    shi[x][y - 1] = min(t, shi[x][y - 1]);
  }
  cout << bfs(s.x, s.y);
  return 0;
}