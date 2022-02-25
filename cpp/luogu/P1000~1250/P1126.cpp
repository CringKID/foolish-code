#include <bits/stdc++.h>
using namespace std;
inline int read() {
  int X = 0;
  bool flag = 1;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    if (ch == '-') flag = 0;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    X = (X << 1) + (X << 3) + ch - '0';
    ch = getchar();
  }
  if (flag) return X;
  return ~(X - 1);
}
void write(int X) {
  if (X < 0) {
    putchar('-');
    X = ~(X - 1);
  }
  if (X > 9) write(X / 10);
  putchar(X % 10 + '0');
}
int cx[4][3] = {{-1, -2, -3}, {0, 0, 0}, {1, 2, 3}, {0, 0, 0}};
int cy[4][3] = {{0, 0, 0}, {-1, -2, -3}, {0, 0, 0}, {1, 2, 3}};
int n, m, fx, fy, mmap[55][55], a[1000005][5];
void bfs() {
  int front = 0, back = 1;
  while (front < back) {
    front++;
    for (int i = 0; i <= 2; i++) {
      int dx = a[front][1] + cx[a[front][3]][i], dy = a[front][2] + cy[a[front][3]][i];
      if (mmap[dx + 1][dy] == 1 || mmap[dx][dy + 1] == 1 || mmap[dx + 1][dy + 1] == 1 || mmap[dx][dy] == 1) break;
      if (dx >= 1 && dx < n && dy >= 1 && dy < m && mmap[dx][dy] == 0) {
        mmap[dx][dy] = 2;
        back++;
        a[back][1] = dx;
        a[back][2] = dy;
        a[back][3] = a[front][3];
        a[back][4] = a[front][4] + 1;
        if (dx == fx && dy == fy) {
          write(a[back][4]);
          return;
        }
      }
    }
    if (a[front][0] != 2)
      for (int j = 1; j <= 3; j++)
        if (j != 2) {
          back++;
          a[back][1] = a[front][1];
          a[back][2] = a[front][2];
          a[back][3] = (a[front][3] + j) % 4;
          a[back][4] = a[front][4] + 1;
          a[back][0] = a[front][0] + 1;
        }
  }
  write(-1);
  return;
}
int main() {
  n = read(), m = read();
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      mmap[i][j] = read();
  char ch;
  a[1][1] = read(), a[1][2] = read();
  mmap[a[1][1]][a[1][2]] = 2;
  fx = read(), fy = read();
  ch = getchar();
  if (a[1][1] == fx && a[1][2] == fy) {
    putchar('0');
    return 0;
  }
  if (ch == 'N')
    a[1][3] = 0;
  else if (ch == 'W')
    a[1][3] = 1;
  else if (ch == 'S')
    a[1][3] = 2;
  else if (ch == 'E')
    a[1][3] = 3;
  bfs();
  return 0;
}