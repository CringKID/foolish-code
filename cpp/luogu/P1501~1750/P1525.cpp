#include <bits/stdc++.h>

using namespace std;
const int kMaxN = 1e5 + 5;

struct crime {
  int x, y, z;
} prison[kMaxN];
int n, m, ene[kMaxN];
class DSU {
 private:
  int father[kMaxN], size;
  int root(int now) {
    return father[now] == now ? now : father[now] = root(father[now]);
  }

 public:
  void init(int n) {
    size = n;
    for (int i = 1; i <= size; i++) {
      father[i] = i;
    }
  }

  void Union(int n1, int n2) {
    n1 = root(father[n1]), n2 = root(father[n2]);
    father[n1] = n2;
  }
  bool Judge(int n1, int n2) {
    n1 = root(n1), n2 = root(n2);
    return n1 == n2;
  }
} dsu;

int main() {
  ios ::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);

  cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    cin >> prison[i].x >> prison[i].y >> prison[i].z;
  }
  sort(prison + 1, prison + m + 1, [](crime c1, crime c2) {
    return c1.z > c2.z;
  });

  dsu.init(n);
  for (int i = 1; i <= m + 1; i++) {
    if (dsu.Judge(prison[i].x, prison[i].y)) {
      cout << prison[i].z << '\n';
      return 0;
    } else {
      if (!ene[prison[i].x]) {
        ene[prison[i].x] = prison[i].y;
      } else {
        dsu.Union(ene[prison[i].x], prison[i].y);
      }
      if (!ene[prison[i].y]) {
        ene[prison[i].y] = prison[i].x;
      } else {
        dsu.Union(ene[prison[i].y], prison[i].x);
      }
    }
  }
  return 0;
}