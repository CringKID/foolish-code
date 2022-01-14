#include <bits/stdc++.h>

using namespace std;
const int kMaxN = 1e5 + 5;
class DSU {
 private:
  int father[kMaxN];
  int root(int now) {
    return now == father[now] ? now : father[now] = root(father[now]);
  }

 public:
  void Init(int n) {
    for (int i = 1; i <= n; i++) {
      father[i] = i;
    }
  }
  void Union(int n1, int n2) {
    father[root(n1)] = root(n2);
  }
  bool Judge(int n1, int n2) {
    return root(n1) == root(n2);
  }
} dsu;

int S[kMaxN], P[kMaxN], s, p, n, k;
double ans;
pair<int, int> edge[kMaxN * 155];
#define x first
#define y second
double dist(int x1, int y1, int x2, int y2) {
  return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}
int main() {
  ios ::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);

  cin >> s >> p;
  for (int i = 1; i <= p; i++) {
    cin >> S[i] >> P[i];
    for (int j = 1; j < i; j++) {
      edge[++n] = make_pair(i, j);
    }
  }
  dsu.Init(p);
  sort(edge + 1, edge + n + 1, [](pair<int, int> n1, pair<int, int> n2) {
    return dist(S[n1.x], P[n1.x], S[n1.y], P[n1.y]) < dist(S[n2.x], P[n2.x], S[n2.y], P[n2.y]);
  });
  for (int i = 1; i <= n; i++) {
    if (!dsu.Judge(edge[i].x, edge[i].y)) {
      dsu.Union(edge[i].x, edge[i].y);
      ans = dist(S[edge[i].x], P[edge[i].x], S[edge[i].y], P[edge[i].y]);
      if ((++k) >= p - s) {
        cout << fixed << setprecision(2) << ans << '\n';
        return 0;
      }
    }
  }
  return 0;
}