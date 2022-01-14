#include <bits/stdc++.h>

using namespace std;
const int kInf = 1e9 + 5, kMaxN = 1e3 + 5;

struct Vector {
  int x, y;                                  // From the Origin to this Spot.
  Vector operator+(Vector& another) const {  // Vector Plus
    return Vector{x + another.x, y + another.y};
  }
  Vector operator-(Vector& another) const {  // Vector Minus
    return Vector{x - another.x, y - another.y};
  }
};
int operator*(Vector v1, Vector v2) {  // Cross Product
  return v1.x * v2.y - v1.y * v2.x;
}
struct Spot {
  int x, y;                                // Coordinate
  Vector operator-(Spot& another) const {  // Generate Vector
    return Vector{x - another.x, y - another.y};
  }
  double operator>>(Spot& another) const {  // Spot Distance
    return sqrt((x - another.x) * (x - another.x) +
                (y - another.y) * (y - another.y));
  }
} spot[kMaxN];

int n, val, visit[kMaxN];
vector<int> v;

int main() {
  ios ::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);

  cin >> n;
  spot[0].x = spot[0].y = kInf;
  for (int i = 1; i <= n; i++) {
    cin >> spot[i].x >> spot[i].y;
    val = (spot[i].y < spot[val].y) ? i : val;
  }
  memset(visit, 0, sizeof(visit));
  visit[val] = 1;
  v.push_back(val);

  Spot sp1 = {0, spot[val].y}, sp2 = spot[val];
  for (int i = 1, now = -1; i < n; i++, now = -1) {
    for (int j = 1; j <= n; j++) {
      if (!visit[j] && (sp2 - sp1) * (spot[j] - sp1) >= 0) {
        if (now == -1) {
          now = j;
          continue;
        }
        int cur = (spot[now] - sp2) * (spot[j] - sp2);
        if (cur < 0 || (cur == 0 && (spot[j] >> sp2) < (spot[now] >> sp2))) {
          now = j;
        }
      }
    }
    if (now == -1) {
      break;
    }
    v.push_back(now);
    visit[now] = true;
    sp1 = sp2;
    sp2 = spot[now];
  }

  cout << n << ' ';
  for (int i = 0; i < v.size(); i++) {
    cout << v[i] << ' ';
  }
  cout << '\n';
  return 0;
}