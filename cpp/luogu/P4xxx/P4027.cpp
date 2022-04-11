#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cmath>

using namespace std;
const int kMaxN = 1e5 + 5;
const double kEps = 1e-9;

struct Node {
  double a, b, rate, k, p, s;
  int idx;
} node[kMaxN], tmp[kMaxN];
int n, stack[kMaxN], top;
double dp[kMaxN];
double slope (int x, int y) {
  if (fabs (node[x].k - node[y].k) < kEps) {
    return 1e20;
  }
  return (node[y].p - node[x].p) / (node[y].k - node[x].k);
}
void solve (int l, int r) {
  if (l == r) {
    dp[l] = max (dp[l], dp[l - 1]);
    node[l].p = dp[l] / (node[l].a * node[l].rate + node[l].b);
    node[l].k = node[l].p * node[l].rate;
    return ;
  }
  int mid = l + r >> 1, t1 = l, t2 = mid + 1;
  for (int i = l; i <= r; i++) {
    if (node[i].idx <= mid) {
      tmp[t1++] = node[i];
    } else {
      tmp[t2++] = node[i];
    }
  }
  for (int i = l; i <= r; i++) {
    node[i] = tmp[i];
  }
  solve (l, mid);
  top = 0;
  for (int i = l; i <= mid; i++) {
    for ( ; top > 1 && slope (stack[top - 1], stack[top]) < slope (stack[top - 1], i) + kEps; top--) {
    }
    stack[++top] = i;
  }
  int tail = 1;
  for (int i = mid + 1; i <= r; i++) {
    for ( ; tail < top && slope (stack[tail], stack[tail + 1]) + kEps > node[i].s; tail++) {
    }
    dp[node[i].idx] = max (dp[node[i].idx], node[i].b * (-node[stack[tail]].k * node[i].s + node[stack[tail]].p));
  }
  solve (mid + 1, r);
  tail = t1 = l, t2 = mid + 1;
  while (t1 <= mid && t2 <= r) {
    if (node[t1].k < node[t2].k || fabs (node[t1].k - node[t2].k) < kEps && node[t1].p < node[t2].p) {
      tmp[tail++] = node[t1++];
    } else {
      tmp[tail++] = node[t2++];
    }
  }
  for ( ; t1 <= mid; tmp[tail++] = node[t1++]) {
  }
  for ( ; t2 <= r; tmp[tail++] = node[t2++]) {
  }
  for (int i = l; i <= r; i++) {
    node[i] = tmp[i];
  }
}
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n >> dp[1];
  for (int i = 1; i <= n; i++) {
    cin >> node[i].a >> node[i].b >> node[i].rate;
  }
  for (int i = 1; i <= n; i++) {
    node[i].s = -node[i].a / node[i].b;
    node[i].idx = i;
  }
  sort (node + 1, node + n + 1, [] (Node n1, Node n2) { return n1.s > n2.s; });
  solve (1, n);
  cout << fixed << setprecision (3) << dp[n] << '\n';
  return 0;
}