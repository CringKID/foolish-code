#include <bits/stdc++.h>

using namespace std;
using ll = long long;
const ll kMaxN = 1e5 + 5, kInf = 55555555555555555, kMod = 2018;

ll n, m, head[kMaxN], dist[kMaxN], tot = 1, ans;
struct Edge {
  ll to, next, val;
} edge[kMaxN];
void add(ll from, ll to, ll val) {
  edge[++tot] = Edge{to, head[from], val}, head[from] = tot;
  edge[++tot] = Edge{from, head[to], 0}, head[to] = tot;
}

queue<ll> q;
bool BFS() {
  memset(dist, -1, sizeof(dist));
  q.push(1), dist[1] = 0;
  while (!q.empty()) {
    int from = q.front();
    q.pop();
    for (int i = head[from]; i; i = edge[i].next) {
      if (dist[edge[i].to] == -1 && edge[i].val > 0) {
        dist[edge[i].to] = dist[from] + 1;
        q.push(edge[i].to);
      }
    }
  }
  return dist[n] != -1;
}
ll DFS(ll now, ll cur) {
  if (now == n) {
    return cur;
  }

  ll ans = 0, tag = 0;
  for (int i = head[now]; i; i = edge[i].next) {
    int to = edge[i].to;
    if (dist[to] == dist[now] + 1 && edge[i].val > 0) {
      tag = DFS(to, min(cur, edge[i].val));
      if (!tag) {
        continue;
      }
      ans += tag;
      cur -= tag;
      edge[i].val -= tag;
      edge[i ^ 1].val += tag;
      if (!cur) {
        break;
      }
    }
  }
  if (!ans) {
    dist[now] = -1;
  }
  return ans;
}

int main() {
  ios ::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);

  cin >> n >> m;
  ll from, to, val;
  for (int i = 1; i <= m; i++) {
    cin >> from >> to >> val;
    add(from, to, val * kMod + 1);
  }
  while (BFS()) {
    ans += DFS(1, kInf);
  }
  cout << ans / kMod << ' ' << ans % kMod << '\n';
  return 0;
}