#include <iostream>
#include <algorithm>

using namespace std;
const int kMaxN = 605, kMaxM = kMaxN * kMaxN, kDir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}}, type[2] = {'X', 'O'};

int n, o, fath[kMaxM], t1, t2, p[2] = {1, 1}, sum[kMaxM];
char Map[kMaxN][kMaxN];
bool tag[kMaxM];
int root (int x) {
  return x == fath[x] ? x : fath[x] = root (fath[x]);
}
int encode (int x, int y) {
  return (x - 1) * n + y;
}
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> Map[i] + 1;
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      t1 = fath[encode (i, j)] = encode (i, j);
      if (Map[i][j] == '.') {
        continue;
      }
      for (int dir = 0; dir < 4; dir++) {
        sum[t1] += (Map[i + kDir[dir][0]][j + kDir[dir][1]] == '.');
      }
      if (Map[i][j] == Map[i - 1][j] && t1 != (t2 = root (encode (i - 1, j)))) {
        sum[t1] += sum[t2], fath[t2] = t1;
      }
      if (Map[i][j] == Map[i][j - 1] && t1 != (t2 = root (encode (i, j - 1)))) {
        sum[t1] += sum[t2], fath[t2] = t1;
      }
    }
  }
  while (p[0] <= t1 && p[1] <= t1) {
    int x = (p[o] - 1) / n + 1, y = (p[o] - 1) % n + 1, s = 0, k = encode (x, y); p[o]++;
    if (Map[x][y] != '.') {
      continue;
    }
    for (int dir = 0; dir < 4; dir++) {
      s += (Map[x + kDir[dir][0]][y + kDir[dir][1]] == '.');
      int nx = x + kDir[dir][0], ny = y + kDir[dir][1];
      if (!isalpha (Map[nx][ny])) {
        continue;
      }
      int fa = root (encode (nx, ny));
      sum[fa]--;
    }
    for (int dir = 0; dir < 4; dir++) {
      int nx = x + kDir[dir][0], ny = y + kDir[dir][1];
      if (!isalpha (Map[nx][ny])) {
        continue;
      }
      int fa = root (encode (nx, ny));
      if (Map[nx][ny] == type[o]) {
        s += (!tag[fa]) * sum[fa], tag[fa] = true;
      } else if (!sum[fa]) {
        s = -1e9;
      }
    }
    for (int dir = 0; dir < 4; dir++) {
      int nx = x + kDir[dir][0], ny = y + kDir[dir][1];
      if (!isalpha (Map[nx][ny])) {
        continue;
      }
      int fa = root (encode (nx, ny));
      tag[fa] = false;
    }
    if (s <= 0) {
      for (int dir = 0; dir < 4; dir++) {
        int nx = x + kDir[dir][0], ny = y + kDir[dir][1];
        if (!isalpha (Map[nx][ny])) {
          continue;
        }
        int fa = root (encode (nx, ny));
        sum[fa]++;
      }
    } else {
      sum[k] = s, Map[x][y] = type[o];
      cout << x << ' ' << y << '\n';
      for (int dir = 0; dir < 4; dir++) {
        int nx = x + kDir[dir][0], ny = y + kDir[dir][1];
        if (!isalpha (Map[nx][ny])) {
          continue;
        }
        int fa = root (encode (nx, ny));
        if (Map[nx][ny] == type[o]) {
          fath[fa] = k;
        }
      }
      o ^= 1;
    }
  }
  cout << -1 << ' ' << -1 << '\n';
  return 0;
}