#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <map>

using namespace std;
const int kMaxN = 255, kMaxM = 4e4 + 5, kInf = 1e9;

bool st[kMaxN], vis[kMaxN];
int n, m, s, t, idg, head[kMaxN], tot, que[kMaxN], cost[kMaxN], cnt;
struct Edge {
  int to, flow, val, next;
} edge[kMaxM];
map <string, int> g; map <int, string> ing;
vector <string> path1, path2;
void add (int from, int to, int flow, int val) {
  edge[tot] = {to, flow, val, head[from]}, head[from] = tot++;
  edge[tot] = {from, 0, -val, head[to]}, head[to] = tot++;
}
void add (int from, int to) {
  edge[tot] = {to, 0, 0, head[from]}, head[from] = tot++;
}
bool BFS () {
  int hd = 0, tl = 1;
  for (int i = 0; i <= t; i++) {
    st[i] = false, cost[i] = kInf;
  }
  que[s] = 0, st[s] = 1, cost[s] = 0;
  while (hd != tl) {
    int from = que[hd++];
    if (hd == kMaxN) {
      hd = 0;
    }
    st[t] = 0;
    for (int i = head[from]; ~i; i = edge[i].next) {
      int to = edge[i].to;
      if (edge[i].flow && cost[to] > cost[t] + edge[i].val) {
        cost[to] = cost[t] + edge[i].val;
        if (!st[to]) {
          st[to] = true;
          que[tl++] = to;
          if (tl == kMaxN) {
            tl = 0;
          }
        }
      }
    }
  }
  return cost[t] != kInf;
}
int DFS (int x, int cur) {
  vis[x] = true;
  if (x == t) {
    return cur;
  }
  int tag = 0;
  for (int i = head[x]; ~i; i = edge[i].next) {
    int to = edge[i].to;
    if (!vis[to] && edge[i].flow && cost[to] == cost[x] + edge[i].val) {
      int tmp;
      if (tmp = DFS (to, min (cur - tag, edge[i].flow))) {
        edge[i].flow -= tmp;
        edge[i ^ 1].flow += tmp;
        tag += tmp, cnt += edge[i].val;
        if (tag == tmp) {
          break;
        }
      }
    }
  }
  return tag;
}
int dinic () {
  int rec = 0;
  while (BFS ()) {
    vis[t] = true;
    while (vis[t]) {
      memset (vis, false, sizeof (vis));
      rec += DFS (s, kInf);
    }
  }
  return rec;
}
void dfs (int x, vector <string> &path) {
  path.push_back (ing[x]);
  vis[x] = true;
  for (int i = head[x]; ~i; i = edge[i].next) {
    int to = edge[i].to;
    if (vis[to]) {
      continue;
    }
    dfs (to, path);
    break;
  }
}
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n >> m;
  memset (head, -1, sizeof (head));
  s = 0, t = n * 2 + 1;
  for (int i = 1; i <= n; i++) {
    string str; cin >> str;
    if (!g.count (str)) {
      g[str] = ++idg;
      ing[idg] = str;
    }
    if (i == 1) {
      add (s, g[str], 2, 0);
    }
    if (i == n) {
      add (g[str] + n, t, 2, 0);
    }
    if (i == 1 || i == n) {
      add (i, i + n, 2, -1);
    } else {
      add (i, i + n, 1, -1);
    }
  }
  int len = tot;
  bool tag = false;
  for (int i = 1; i <= m; i++) {
    string str1, str2;
    cin >> str1 >> str2;
    add (g[str1] + n, g[str2], 1, 0);
    if (g[str1] == 1 && g[str2] == n) {
      tag = true;
    }
  }
  int len2 = tot, rec = dinic ();
  if (rec == 1 && tag) {
    cout << 2 << '\n' << ing[1] << '\n' << ing[n] << '\n' << ing[1] << '\n';
    return 0;
  }
  if (rec != 2) {
    cout << "No Solution!" << '\n';
    return 0;
  } else {
    cout << -cnt - 2 << '\n';
  }
  tot = 0;
  memset (head, -1, sizeof (head));
  for (int i = len; i < len2; i++) {
    if (i & 1 && edge[i].flow) {
      int a = edge[i].to - n, b = edge[i ^ 1].to;
      add (a, b);
    }
  }
  memset (vis, false, sizeof (vis));
  dfs (1, path1), dfs (1, path2);
  reverse (path2.begin (), path2.end ());
  for (string str : path1) {
    cout << str << '\n';
  }
  for (string str : path2) {
    cout << str << '\n';
  }
  return 0;
}