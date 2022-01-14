#include <bits/stdc++.h>
using namespace std;
struct node {
  int value, place;
  friend bool operator<(const node &x, const node &y) {
    return x.value < y.value;
  }
};
const int maxn = 2e5 + 5;
priority_queue<node> pq;
int n, m, ans, chose, Next[maxn], pre[maxn], w[maxn], l, r;
bool vis[maxn];
void update(int num) {
  vis[num] = 1;
  Next[pre[num]] = Next[num];
  pre[Next[num]] = pre[num];
  Next[num] = pre[num] = 0;
}
int main() {
  scanf("%d %d", &n, &m);
  for (register int i = 1; i <= n; i++) scanf("%d", &w[i]);
  if ((n >> 1) < m) {
    puts("Error!");
    return 0;
  }
  for (register int i = 1; i < n; i++) Next[i] = i + 1;
  for (register int i = 2; i <= n; i++) pre[i] = i - 1;
  for (register int i = 1; i <= n; i++) pq.push((node){w[i], i});
  Next[n] = 1, pre[1] = n;
  for (register int i = 1; i <= m; i++) {
    while (vis[pq.top().place]) pq.pop();
    node front = pq.top();
    pq.pop();
    ans += front.value;
    l = pre[front.place], r = Next[front.place];
    w[front.place] = w[l] + w[r] - w[front.place];
    update(l), update(r);
    pq.push((node){w[front.place], front.place});
  }
  printf("%d\n", ans);
  return 0;
}