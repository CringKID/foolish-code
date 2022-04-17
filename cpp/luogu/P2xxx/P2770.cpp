#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
#include <map>

using namespace std;
const int kMaxN = 1e3 + 5, kMaxM = 1e6 + 5, kInf = 0x7fffffff;

queue <int> que;
int n, v, s, t, cnt = 1, dis[kMaxN], Flow[kMaxN], head[kMaxN], road[kMaxN], arr1[kMaxN], arr2[kMaxN], nhead[kMaxN], sta[kMaxN], top;
struct Edge {
  int to, dist, next, flow;
} edge[kMaxM];
map <string, int> Map;
string str[kMaxN], str1, str2;
bool vis[kMaxN];
void add (int from, int to, int dist, int flow) {
  edge[++cnt] = {to, dist, head[from], flow};
  head[from] = cnt;
  edge[++cnt] = {from, -dist, head[to], 0};
  head[to] = cnt;
}
void add (int from, int to) {
  edge[++cnt] = {to, 0, nhead[from], 0};
  nhead[from] = cnt;
}
bool SPFA () {
  for (int i = 1; i <= n << 1; i++) {
    dis[i] = -kInf, Flow[i] = kInf;
  }
  dis[s] = 0, que.push (s);
  while (!que.empty ()) {
    int from = que.front (); que.pop (), vis[from] = false;
    for (int i = head[from]; i; i = edge[i].next) {
      int to = edge[i].to;
      if (dis[to] < dis[from] + edge[i].dist && edge[i].flow > 0) {
        dis[to] = dis[from] + edge[i].dist;
        Flow[to] = min (Flow[from], edge[i].flow);
        road[to] = i;
        if (!vis[to]) {
          vis[to] = true, que.push (to);
        }
      }
    }
  }
  return Flow[t] != kInf;
}
void DFS (int x) {
  sta[++top] = x, vis[x] = true;
  for (int i = nhead[x]; i; i = edge[i].next) {
    int to = edge[i].to;
    if (!vis[to]) {
      DFS (to);
    }
  }
}
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n >> v, s = 1, t = n << 1;
  for (int i = 1; i <= n; i++) {
    cin >> str[i];
    Map[str[i]] = i;
    add (i, i + n, 1, 1);
  }
  add (s, s + n, 0, 1);
  add (n, n + n, 0, 1);
  for (int i = 1; i <= v; i++) {
    cin >> str1 >> str2;
    if (Map[str1] > Map[str2]) {
      swap (str1, str2);
    }
    arr1[i] = Map[str1], arr2[i] = Map[str2];
    add (Map[str1] + n, Map[str2], 0, 1);
  }
  int flow = 0, cost = 0;
  while (SPFA ()) {
    flow += Flow[t], cost += Flow[t] * dis[t];
    for (int i = t; i != s; i = edge[road[i] ^ 1].to) {
      edge[road[i]].flow -= Flow[t];
      edge[road[i] ^ 1].flow += Flow[t];
    }
  }
  if (cost == 2) {
    cout << 2 << '\n';
    cout << str[1] << '\n' << str[n] << '\n' << str[1] << '\n';
  } else if (flow == 2) {
    cout << cost << '\n';
    for (int i = 1; i <= v; i++) {
      for (int j = head[arr1[i] + n]; j; j = edge[j].next) {
        if (edge[j].to == arr2[i] && !edge[j].flow) {
          add (arr1[i], arr2[i]), add (arr2[i], arr1[i]);
        }
      }
    }
    DFS (s);
    for (int i = 1; i <= top; i++) {
      cout << str[sta[i]] << '\n';
    }
    cout << str[1] << '\n';
  } else {
    cout << "No Solution!" << '\n';
  }
  return 0;
}