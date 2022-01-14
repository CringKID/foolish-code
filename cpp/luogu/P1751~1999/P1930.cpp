#include <bits/stdc++.h>

using namespace std;
const int kMaxN = 55, kMaxM = 2555, dir[8][2] = {{1, 2}, {2, 1}, {2, -1}, {1, -2}, {-1, -2}, {-2, -1}, {-2, 1}, {-1, 2}};

struct Spot {
  int l, c, d;
} spot[kMaxM], sp;
int st, r, c, ans = 1e9, sum, dist[kMaxN][kMaxN][kMaxN][kMaxN];
bool vis[kMaxN][kMaxN];
queue<Spot> q;

bool checkpoint(int x, int y) {
  return x <= 0 || x > r || y <= 0 || y > c;
}
void BFS(int fx, int fy) {
  memset(vis, false, sizeof(vis));
  q.push((Spot){fx, fy, 0});
  vis[fx][fy] = 1;
  dist[fx][fy][fx][fy] = 0;
  while (!q.empty()) {
    int nx = q.front().l, ny = q.front().c;
    dist[fx][fy][nx][ny] = q.front().d;
    q.pop();
    for (int i = 0; i < 8; i++) {
      int dx = nx + dir[i][0], dy = ny + dir[i][1];
      if (!checkpoint(dx, dy) && !vis[dx][dy]) {
        vis[dx][dy] = true;
        q.push((Spot){dx, dy, dist[fx][fy][nx][ny] + 1});
      }
    }
  }
}

int main() {
  ios ::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);

  cin >> r >> c;
  memset(dist, 0x10f, sizeof(dist));
  char ch;
  int sum;
  while (cin >> ch >> sum) {
    if (!st) {
      st = 1;
      sp.l = sum, sp.c = ch - 'A' + 1;
    } else {
      spot[st].l = sum, spot[st++].c = ch - 'A' + 1;
    }
  }
  st--;

  for (int i = 1; i <= r; i++) {
    for (int j = 1; j <= c; j++) {
      BFS(i, j);
    }
  }
  for (int i = 1; i <= r; i++) {
    for (int j = 1; j <= c; j++) {
      int cur = 0;
      for (int k = 1; k <= st; k++) {
        cur += dist[spot[k].l][spot[k].c][i][j];
      }
      ans = min(ans, cur + max(abs(sp.l - i), abs(sp.c - j)));
      for (int k = 1, cnt = cur; k <= st; k++, cnt = cur) {
        cnt -= dist[spot[k].l][spot[k].c][i][j];
        for (int I = max(1, sp.l - 3); I <= min(r, sp.l + 3); I++) {
          for (int J = max(1, sp.c - 3); J <= min(c, sp.c + 3); J++) {
            ans = min(cnt + dist[spot[k].l][spot[k].c][I][J] + max(abs(I - sp.l), abs(J - sp.c)) + dist[I][J][i][j], ans);
          }
        }
      }
    }
  }
  cout << ans << '\n';
  return 0;
}