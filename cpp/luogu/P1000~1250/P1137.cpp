#include <bits/stdc++.h>
using namespace std;
queue<int> q;
int n, m, x, y, dis[10000001], num, in[10000001], head[10000001];
struct node {
  int to, next;
} stu[10000001];
int main() {
  scanf("%d %d", &n, &m);
  for (int i = 1; i <= m; i++) {
    scanf("%d %d", &x, &y);
    in[y]++;
    stu[++num].next = head[x];
    stu[num].to = y;
    head[x] = num;
  }
  for (int i = 1; i <= n; i++)
    if (in[i] == 0) {
      q.push(i);
      dis[i] = 1;
    }
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (int i = head[u]; i != 0; i = stu[i].next) {
      int k = stu[i].to;
      --in[k];
      if (in[k] == 0) {
        q.push(k);
        dis[k] = dis[u] + 1;
      }
    }
  }
  for (int i = 1; i <= n; i++) printf("%d\n", dis[i]);
  return 0;
}