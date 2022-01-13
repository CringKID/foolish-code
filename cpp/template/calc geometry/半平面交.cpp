#include <bits/stdc++.h>

using namespace std;
const int kMaxN = 1e3 + 5;
const double eps = 1e-12;

int n, m, cnt, head = 1, tail = 1;
double ans;
struct Spot {
  double x, y;
  Spot(double x_, double y_) : x(x_), y(y_) {
  }
  Spot() {
  }

  Spot operator+(const Spot& another) const {
    return Spot(x + another.x, y + another.y);
  }
  Spot operator-(const Spot& another) const {
    return Spot(x - another.x, y - another.y);
  }
  Spot operator*(const double& cur) const {
    return Spot(x * cur, y * cur);
  }
} spot[kMaxN], tmp[kMaxN];
struct Line {
  Spot a, b;
  double k;
  Line(Spot a_, Spot b_) : a(a_), b(b_) {
    k = atan2(b.y, b.x);
  }
  Line() {
  }
  bool operator<(const Line& another) const {
    return k < another.k;
  }
} line[kMaxN], arr[kMaxN];

double Xmul(Spot s1, Spot s2) {
  return s1.x * s2.y - s1.y * s2.x;
}
Spot Getspot(Line l1, Line l2) {
  Spot sp = l1.a - l2.a;
  double k = Xmul(l2.b, sp) / Xmul(l1.b, l2.b);
  return l1.a + l1.b * k;
}

int main() {
  ios ::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);

  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> m;
    for (int j = 1; j <= m; j++) {
      cin >> spot[j].x >> spot[j].y;
    }
    for (int j = 1, cur; j <= m; j++) {
      cur = (j == m ? 1 : j + 1);
      line[++cnt] = Line(spot[j], spot[cur] - spot[j]);
    }
  }
  sort(line + 1, line + cnt + 1);

  arr[1] = line[1];
  for (int i = 2; i <= cnt; i++) {
    for (; head < tail && Xmul(line[i].b, tmp[tail - 1] - line[i].a) <= eps; tail--) {
    }
    for (; head < tail && Xmul(line[i].b, tmp[head] - line[i].a) <= eps; head++) {
    }

    arr[++tail] = line[i];
    if (fabs(Xmul(arr[tail].b, arr[tail - 1].b)) <= eps) {
      tail--;
      if (Xmul(arr[tail].b, line[i].a - arr[tail].a) > eps) {
        arr[tail] = line[i];
      }
    }
    if (head < tail) {
      tmp[tail - 1] = Getspot(arr[tail - 1], arr[tail]);
    }
  }
  for (; head < tail && Xmul(arr[head].b, tmp[tail - 1] - arr[head].a) <= eps; tail--) {
  }
  if (head < tail) {
    tmp[tail] = Getspot(arr[head], arr[tail]);
  }
  for (int i = head, cur; i <= tail; i++) {
    cur = (i == tail ? head : i + 1);
    ans += Xmul(tmp[i], tmp[cur]);
  }
  cout << fixed << setprecision(3) << ans / 2 << '\n';
  return 0;
}