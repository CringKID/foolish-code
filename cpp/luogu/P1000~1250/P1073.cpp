#include <bits/stdc++.h>
using namespace std;
int n, m, prize[100005], dpmin[100005], dpget[100005], x, y, z, cnt, head[100005], indegree[100005];
int MaxPrize[100005], MinPrize[100005];
int belong[100005], number;
struct road {
  int to, next;
} r[1000005], edge[1000005];
int newHead[100005];
void add(int a, int b) {
  r[++cnt].to = b;
  r[cnt].next = head[a];
  head[a] = cnt;
}
int dfn[100005], low[100005], vis[100005], tot;
stack<int> s;
void tarjan(int x) {
  dfn[x] = low[x] = ++tot;
  s.push(x);
  vis[x] = 1;
  for (int i = head[x]; i != 0; i = r[i].next) {
    int v = r[i].to;
    if (dfn[v] == 0) {
      tarjan(v);
      low[x] = min(low[x], low[v]);
    } else if (vis[v] == 1) {
      low[x] = min(low[x], low[v]);
    }
  }
  if (low[x] == dfn[x]) {
    number++;
    MaxPrize[number] = MinPrize[number] = prize[x];
    while (s.top() != x) {
      belong[s.top()] = number;
      vis[s.top()] = 0;
      if (MaxPrize[number] < prize[s.top()]) {
        MaxPrize[number] = prize[s.top()];
      }
      if (MinPrize[number] > prize[s.top()]) {
        MinPrize[number] = prize[s.top()];
      }
      s.pop();
    }
    belong[x] = number;
    vis[x] = 0;
    s.pop();
  }
}
void addEdge(int a, int b) {
  edge[++cnt].to = b;
  edge[cnt].next = newHead[a];
  newHead[a] = cnt;
  indegree[b]++;
}
int main() {
  scanf("%d %d", &n, &m);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &prize[i]);
  }
  for (int i = 0; i < m; i++) {
    scanf("%d %d %d", &x, &y, &z);
    add(x, y);
    if (z == 2) add(y, x);
  }
  for (int i = 1; i <= n; i++) {
    if (dfn[i] == 0) {
      tarjan(i);
    }
  }
  cnt = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = head[i]; j != 0; j = r[j].next) {
      int v = r[j].to;
      if (belong[i] == belong[v]) {
        continue;
      }
      addEdge(belong[i], belong[v]);
    }
  }
  queue<int> q;
  for (int i = 1; i <= number; i++) {
    dpmin[i] = MinPrize[i];
    if (indegree[i] == 0)
      q.push(i);
  }
  while (!q.empty()) {
    int front = q.front();
    q.pop();
    for (int i = newHead[front]; i != 0; i = edge[i].next) {
      int v = edge[i].to;
      indegree[v]--;
      if (indegree[v] == 0) q.push(v);
      dpmin[v] = min(dpmin[v], dpmin[front]);
      dpget[v] = max(dpget[v], MaxPrize[v] - dpmin[v]);
      dpget[v] = max(dpget[v], dpget[front]);
      dpget[v] = max(dpget[v], MaxPrize[v] - MinPrize[v]);
    }
  }
  printf("%d\n", dpget[belong[n]]);
  return 0;
}