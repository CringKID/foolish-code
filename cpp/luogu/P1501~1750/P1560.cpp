#include <bits/stdc++.h>

using namespace std;
const int kMaxN = 155, dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

int v, m, n, ans, matrix[kMaxN][kMaxN];
char ch;
void DFS(int nx, int ny, int dire, int cur) {
  ans = max(ans, cur);
  if (matrix[nx + dir[dire][0]][ny + dir[dire][1]] == 1) {
    matrix[nx][ny] = 2;
    DFS(nx + dir[dire][0], ny + dir[dire][1], dire, cur + 1);
    matrix[nx][ny] = 1;
  } else if (matrix[nx + dir[dire][0]][ny + dir[dire][1]] == 0) {
    for (int i = 0; i < 4; i++) {
      if ((matrix[nx + dir[i][0]][ny + dir[i][1]] == 1) && ((i + dire) % 2 != 0)) {
        matrix[nx][ny] = 2;
        DFS(nx + dir[i][0], ny + dir[i][1], i, cur + 1);
        matrix[nx][ny] = 1;
      }
    }
  }
}

int main() {
  ios ::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);

  cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    cin >> ch >> v;
    matrix[ch - 'A' + 1][v] = 1;
  }

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      if (matrix[i][j] == 1) {
        matrix[i][j] = 0;
      } else {
        matrix[i][j] = 1;
      }
    }
  }
  DFS(1, 1, 0, 1), DFS(1, 1, 1, 1);

  cout << ans << '\n';
  return 0;
}