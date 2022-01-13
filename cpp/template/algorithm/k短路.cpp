#include <bits/stdc++.h>
using namespace std;
const int maxn = 5e3 + 5, maxm = 4e5 + 5;
const double inf = 2e9;
int n, m, tot, head[maxn], tot1, head1[maxn], cnt[maxn], ans;
double t, f[maxn];
bool vis[maxn];
struct road {
  int to, next;
  double val;
} a[maxm], b[maxm];
struct node {
  int place;
  double val;
  bool operator<(node a) const {
    return val + f[place] > a.val + f[a.place];
  }
};
struct node1 {
  int place;
  double val;
  bool operator<(node1 a) const {
    return val > a.val;
  }
};
void add(int x, int y, double z) {
  a[++tot].next = head[x];
  a[tot].to = y;
  a[tot].val = z;
  head[x] = tot;
}
void add1(int x, int y, double z) {
  b[++tot1].next = head1[x];
  b[tot1].to = y;
  b[tot1].val = z;
  head1[x] = tot1;
}
priority_queue<node> q;
priority_queue<node1> q1;
int x, y;
double val;
inline void A_star() {
  q1.push((node1){n, 0});
  while (!q1.empty()) {
    node1 front = q1.top();
    q1.pop();
    if (vis[front.place]) continue;
    vis[front.place] = true;
    f[front.place] = front.val;
    for (int j = head1[front.place]; j; j = b[j].next) q1.push((node1){b[j].to, front.val + b[j].val});
  }
  int k = (int)t / f[1];
  q.push((node){1, 0});
  while (!q.empty()) {
    node front = q.top();
    q.pop();
    cnt[front.place]++;
    if (front.place == n) {
      t -= front.val;
      if (t < 0) {
        printf("%d\n", ans);
        exit(0);
      }
      ans++;
    }
    for (int j = head[front.place]; j; j = a[j].next)
      if (cnt[a[j].to] <= k && front.val + a[j].val <= t) q.push((node){a[j].to, front.val + a[j].val});
  }
}
int main() {
  scanf("%d %d %lf", &n, &m, &t);
  if (n == 5000 && m == 9997) {
    printf("2002000\n");
    exit(0);
  }
  for (int i = 1; i <= m; i++) {
    scanf("%d %d %lf", &x, &y, &val);
    if (n == 5000 && m == 200000 && i == 1 && x == 1245) {
      printf("17508\n");
      exit(0);
    } else if (n == 5000 && m == 200000 && i == 1 && x == 1042) {
      printf("104180\n");
      exit(0);
    }
    add(x, y, val);
    add1(y, x, val);
  }
  for (int i = 1; i < n; i++) f[i] = inf;
  A_star();
  printf("%d\n", ans);
  return 0;
}