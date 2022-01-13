#include <bits/stdc++.h>
using namespace std;
int d[100001], n, m, a, b, c, s;
bool vis[100001];
struct road {
  int from, to, len;
};
struct node {
  int id, len;
  friend bool operator<(const node &a, const node &b) {
    return a.len > b.len;
  }
};
vector<road> v[100001];
void pqDijkstra(int start) {
  for (int i = 1; i <= n; i++) d[i] = INT_MAX;
  d[start] = 0;
  priority_queue<node> pq;
  pq.push((node){start, 0});
  while (!pq.empty()) {
    node head = pq.top();
    pq.pop();
    int from = head.id, to, len;
    if (vis[from]) continue;
    vis[from] = 1;
    for (int j = 0; j < v[from].size(); j++) {
      to = v[from][j].to, len = v[from][j].len;
      if (d[from] + len < d[to]) {
        d[to] = d[from] + len;
        pq.push((node){to, d[to]});
      }
    }
  }
  for (int i = 1; i <= n; i++) printf("%d ", d[i]);
}
int main() {
  scanf("%d %d %d", &n, &m, &s);
  for (int i = 0; i < m; i++) {
    scanf("%d %d %d", &a, &b, &c);
    v[a].push_back((road){a, b, c});
  }
  pqDijkstra(s);
  return 0;
}