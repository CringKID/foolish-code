#include <bits/stdc++.h>

using namespace std;
const int kMaxN = 1e5 + 5;

int n;
struct Node {
  double x, y;
} node[kMaxN], ans[kMaxN];
double crosspro(Node as, Node ae, Node bs, Node be) {
  return (ae.x - as.x) * (be.y - bs.y) - (be.x - bs.x) * (ae.y - as.y);
}
double dist(Node n1, Node n2) {
  return sqrt((n1.x - n2.x) * (n1.x - n2.x) + (n1.y - n2.y) * (n1.y - n2.y));
}

int main() {
  ios ::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);

  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> node[i].x >> node[i].y;
    if (i != 1 & node[i].y < node[1].y) {
      swap(node[1], node[i]);
    }
  }
  sort(node + 2, node + n + 1, [](Node n1, Node n2) {
    double tmp = crosspro(node[1], n1, node[1], n2);
    if (tmp > 0 || tmp == 0 && dist(node[0], n1) < dist(node[0], n2)) {
      return true;
    }
    return false;
  });
  ans[1] = node[1];

  int reg = 1;
  for (int i = 2; i <= n; i++) {
    while (reg > 1 && crosspro(ans[reg - 1], ans[reg], ans[reg], node[i]) < 0) {
      reg--;
    }
    ans[++reg] = node[i];
  }
  ans[++reg] = node[1];

  double ansdist = 0;
  for (int i = 1; i < reg; i++) {
    ansdist += dist(ans[i], ans[i + 1]);
  }
  cout << fixed << setprecision(2) << ansdist << '\n';
  return 0;
}