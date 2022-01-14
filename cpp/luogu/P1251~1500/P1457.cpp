#include <bits/stdc++.h>

using namespace std;

const int kMaxN = 55, dx[4] = {0, -1, 0, 1}, dy[4] = {-1, 0, 1, 0};
int n, m, mmap[kMaxN][kMaxN][5], matrix[kMaxN][kMaxN], d, s, arr[kMaxN * kMaxN], ans;

void DFS(int nx, int ny) {
  matrix[nx][ny] = s;
  for (int i = 1; i <= 4; i++) {
    if (mmap[nx][ny][i] == 0 && matrix[nx + dx[i - 1]][ny + dy[i - 1]] == 0) {
      arr[s]++;
      DFS(nx + dx[i - 1], ny + dy[i - 1]);
    }
  }
}

int main() {
  ios ::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);

  cin >> m >> n;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      cin >> d;
      if (d % 2 == 1) {
        mmap[i][j][1] = 1;
      }
      d /= 2;
      if (d % 2 == 1) {
        mmap[i][j][2] = 1;
      }
      d /= 2;
      if (d % 2 == 1) {
        mmap[i][j][3] = 1;
      }
      d /= 2;
      if (d % 2 == 1) {
        mmap[i][j][4] = 1;
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (matrix[i][j] == 0) {
        s++;
        arr[s] = 1;
        DFS(i, j);
      }
    }
  }

  cout << s << '\n';
  for (int i = 1; i <= s; i++) {
    ans = max(ans, arr[i]);
  }
  cout << ans << '\n';
  ans = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      for (int k = 3; k <= 4; k++) {
        if (mmap[i][j][k] == 1 && matrix[i][j] != matrix[i + dx[k - 1]][j + dy[k - 1]]) {
          ans = max(ans, arr[matrix[i][j]] + arr[matrix[i + dx[k - 1]][j + dy[k - 1]]]);
        }
      }
    }
  }
  cout << ans << '\n';

  for (int j = 1; j <= m; j++) {
    for (int k = 2; k <= 3; k++) {
      for (int i = n; i >= 1; i--) {
        if (mmap[i][j][k] == 1 && matrix[i][j] != matrix[i + dx[k - 1]][j + dy[k - 1]] &&
            arr[matrix[i][j]] + arr[matrix[i + dx[k - 1]][j + dy[k - 1]]] == ans) {
          cout << i << ' ' << j << ' ';
          if (k == 3) {
            cout << "E" << '\n';
          } else if (k == 2) {
            cout << "N" << '\n';
          }
          return 0;
        }
      }
    }
  }
}