#include <bits/stdc++.h>

using namespace std;
const int kMaxN = 155;

class DisJointSet {
 private:
  int father[kMaxN], n;

 public:
  int Root(int now) {
    return father[now] == now ? now : father[now] = Root(father[now]);
  }
  void init(int cur) {
    this->n = cur;
    for (int i = 1; i <= n; i++) {
      father[i] = i;
    }
  }
  void Union(int x, int y) {
    x = Root(x), y = Root(y);
    if (x != y) {
      father[y] = x;
    }
  }
  bool Judge(int x, int y) {
    return Root(x) == Root(y);
  }
} dsu;
struct Spot {
  int x, y;
} spot[kMaxN];
char ch[kMaxN];
double mmap[kMaxN][kMaxN], mmax[kMaxN], arr[kMaxN];
double Dist(double x1, double y1, double x2, double y2) {
  return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

int main() {
  int n;
  cin >> n;
  dsu.init(n);
  for (int i = 1; i <= n; i++) {
    cin >> spot[i].x >> spot[i].y;
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      char tmp = getchar();
      while (tmp != '1' && tmp != '0') {
        tmp = getchar();
      }
      if (i == j) {
        mmap[i][j] = 0;
      } else if (tmp == '1') {
        mmap[i][j] = Dist(spot[i].x, spot[i].y, spot[j].x, spot[j].y);
        dsu.Union(i, j);
      } else {
        mmap[i][j] = 1 << 30;
      }
    }
  }

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      for (int k = 1; k <= n; k++) {
        mmap[j][k] = min(mmap[j][k], mmap[j][i] + mmap[i][k]);
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      if (dsu.Judge(i, j)) {
        mmax[i] = max(mmax[i], mmap[i][j]);
      }
    }
    arr[dsu.Root(i)] = max(arr[dsu.Root(i)], mmax[i]);
  }

  double ans = 1 << 30;
  for (int i = 1; i <= n; i++) {
    for (int j = i + 1; j <= n; j++) {
      if (!dsu.Judge(i, j)) {
        ans = min(ans, max(mmax[i] + mmax[j] + Dist(spot[i].x, spot[i].y, spot[j].x, spot[j].y),
                           max(arr[dsu.Root(i)], arr[dsu.Root(j)])));
      }
    }
  }
  cout << fixed << setprecision(6) << ans << '\n';
  return 0;
}