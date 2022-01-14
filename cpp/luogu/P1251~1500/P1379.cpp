#include <bits/stdc++.h>
using namespace std;
int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
string target = "123804765", s;
bool flag = 0;
int h(string now, string end) {
  int ans = 0;
  for (int i = 0; i < now.size(); i++) {
    if (now[i] == '0') continue;
    int j = end.find(now[i]), sx = i / 3, sy = i % 3, ex = j / 3, ey = j % 3;
    ans += (abs(sx - ex) + abs(sy - ey));
  }
  return ans;
}
void ida_star(int depth, int maxdepth, string now, int nx, int ny) {
  if (depth + h(now, target) > maxdepth) return;
  if (now == target) {
    flag = 1;
    return;
  }
  if (flag) return;
  for (int i = 0; i < 4; i++) {
    int dx = nx + dir[i][0], dy = ny + dir[i][1];
    if (dx < 1 || dx > 3 || dy < 1 || dy > 3) continue;
    swap(now[(dx - 1) * 3 + dy - 1], now[(nx - 1) * 3 + ny - 1]);
    ida_star(depth + 1, maxdepth, now, dx, dy);
    if (flag) return;
    swap(now[(dx - 1) * 3 + dy - 1], now[(nx - 1) * 3 + ny - 1]);
  }
  return;
}
int main() {
  cin >> s;
  if (s == target) {
    printf("0\n");
    return 0;
  }
  int temp = h(s, target) - 1;
  int nx, ny;
  for (int i = 0; i < 9; i++)
    if (s[i] == '0') {
      nx = i / 3 + 1;
      ny = i % 3 + 1;
      break;
    }
  while (++temp) {
    ida_star(0, temp, s, nx, ny);
    if (flag) {
      printf("%d\n", temp);
      break;
    }
  }
  return 0;
}