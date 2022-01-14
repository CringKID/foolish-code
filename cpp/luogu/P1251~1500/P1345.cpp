#include <bits/stdc++.h>

using namespace std;
const int kMaxN = 255, kInf = 0x3f3f3f3f;

struct Edge {
  int to, val, flow;
  Edge(int sum1, int sum2, int sum3) : to(sum1), val(sum2), flow(sum3) {}
};
vector<Edge> edge[kMaxN];
void add(int from, int to, int val) {
  edge[from].push_back(Edge(to, val, edge[to].size()));
  edge[to].push_back(Edge(from, 0, edge[from].size()));
}

int n, m, sum1, sum2, depth[kMaxN];
queue<int> q;
bool BFS() {
  memset(depth, 0, sizeof(depth));
  depth[sum1] = 1;
  q.push(sum1);
  while (!q.empty()) {
    int from = q.front();
    q.pop();
    for (int i = 0; i < edge[from].size(); i++) {
      if (edge[from][i].val > 0 && depth[edge[from][i].to] == 0) {
        depth[edge[from][i].to] = depth[from] + 1;
        q.push(edge[from][i].to);
      }
    }
  }
  return depth[sum2] != 0;
}

int DFS(int now, int cur) {
  if (now == sum2) {
    return cur;
  }
  int ans = 0;
  for (int i = 0; i < edge[now].size(); i++) {
    if (edge[now][i].val > 0 && depth[edge[now][i].to] == depth[now] + 1) {
      int tmp = DFS(edge[now][i].to, min(cur, edge[now][i].val));
      edge[now][i].val -= tmp;
      edge[edge[now][i].to][edge[now][i].flow].val += tmp;
      cur -= tmp, ans += tmp;
      if (cur == 0) {
        break;
      }
    }
  }
  return ans;
}
int main() {
  ios ::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);

  cin >> n >> m >> sum1 >> sum2;
  for (int i = 1; i <= n; i++) {
    edge[i].reserve(8);
  }
  for (int i = 1; i <= n; i++) {
    if (i == sum1 || i == sum2) {
      add(i, i + n, kInf);
    } else {
      add(i, i + n, 1);
    }
  }
  for (int from, to, i = 1; i <= m; i++) {
    cin >> from >> to;
    add(from + n, to, kInf);
    add(to + n, from, kInf);
  }

  int ans = 0;
  while (BFS()) {
    ans += DFS(sum1, kInf);
  }
  cout << ans << '\n';
  return 0;
}