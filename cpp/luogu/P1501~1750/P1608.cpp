#include <bits/stdc++.h>
using namespace std;
int n, e, a, b, c, d[2005], vis[2005], r[2005][2005];
long long ans[2005];
struct node {
  int nodee, cost;
  friend bool operator<(const node &x, const node &y) {
    return x.cost > y.cost;
  }
};
priority_queue<node> pq;
void Dijkstra() {
  for (int i = 1; i <= n; i++) d[i] = 1e9;
  d[1] = 0;
  pq.push((node){1, 0});
  ans[1] = 1;
  while (!pq.empty()) {
    node top = pq.top();
    pq.pop();
    if (vis[top.nodee]) continue;
    vis[top.nodee] = 1;
    int from = top.nodee, to, len;
    for (int i = 1; i <= n; i++) {
      if (r[top.nodee][i] == 0) continue;
      to = i, len = r[top.nodee][i];
      if (d[from] + len < d[to]) {
        d[to] = d[from] + len;
        pq.push((node){to, d[to]});
        ans[to] = ans[from];
      } else if (d[from] + len == d[to])
        ans[to] += ans[from];
    }
  }
}
int main() {
  cin >> n >> e;
  for (int i = 0; i < e; i++) {
    cin >> a >> b >> c;
    if (r[a][b] == 0)
      r[a][b] = c;
    else
      r[a][b] = min(r[a][b], c);
  }
  Dijkstra();
  if (d[n] == 1e9) {
    cout << "No answer" << endl;
    return 0;
  }
  cout << d[n] << ' ' << ans[n] << endl;
  return 0;
}