#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e3 + 5;
const double down = 0.997;
int n;
struct thing {
  int x, y, val;
} things[maxn];
struct node {
  double x, y, val;
} ans;
inline double energy(double x, double y) {
  register double cnt = 0, dx, dy;
  for (register int i = 1; i <= n; i++) {
    dx = x - things[i].x, dy = y - things[i].y;
    cnt += sqrt(dx * dx + dy * dy) * things[i].val;
  }
  return cnt;
}
inline void SA() {
  register double temperature = 3e3 + 5;
  while (temperature > 1e-15) {
    register double dx = ans.x + (rand() * 2 - RAND_MAX) * temperature, dy = ans.y + (rand() * 2 - RAND_MAX) * temperature, dval = energy(dx, dy);
    if (dval < ans.val)
      ans = (node){dx, dy, dval};
    else if (exp((ans.val - dval) / temperature) * RAND_MAX > rand())
      ans = (node){dx, dy, ans.val};
    temperature *= down;
  }
}
int main() {
  srand(19260817);
  scanf("%d", &n);
  for (register int i = 1; i <= n; i++) scanf("%d %d %d", &things[i].x, &things[i].y, &things[i].val), ans.x += things[i].x, ans.y += things[i].y;
  ans.x /= n, ans.y /= n, ans.val = energy(ans.x, ans.y);
  while ((double)clock() / CLOCKS_PER_SEC < 0.95) SA();
  printf("%.3lf %.3lf\n", ans.x, ans.y);
  return 0;
}