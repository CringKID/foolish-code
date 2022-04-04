#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;
const int kMaxN = 505, kMaxM = 1e5 + 5, kInf = 1e9;

struct Edge {
  int to, next, val;
} edge[kMaxM << 1];
int tot = 1, head[kMaxN << 1], n, m, S, T, arr[kMaxN], f[kMaxN], dis[kMaxN << 1], nhead[kMaxN << 1], maxflow;
void add (int from, int to, int val) {
  edge[++tot] = {to, head[from], val}, head[from] = tot;
  edge[++tot] = {from, head[to], 0}, head[to] = tot;
}
bool BFS () {
  copy_n (head, T + 1, nhead), fill_n (dis, T + 1, kInf);
  queue <int> que; que.push (S), dis[S] = 0;
  while (!que.empty ()) {
    int from = que.front (); que.pop ();
    for (int i = head[from]; i; i = edge[i].next) {
      int to = edge[i].to;
      if (dis[to] == kInf && edge[i].val) {
        dis[to] = dis[from] + 1;
        if (to == T) {
          return true;
        }
        que.push (to);
      }
    }
  }
  return false;
}
int DFS (int x, int cur) {
  if (x == T) {
    return cur;
  }
  if (!cur) {
    return 0;
  }
  int rec = 0;
  for (int i = nhead[x]; i && cur; i = edge[i].next) {
    nhead[x] = i;
    int v = edge[i].to;
    if (dis[v] == dis[x] + 1 && edge[i].val) {
      int tmp = DFS (v, min (edge[i].val, cur));
      edge[i].val -= tmp, edge[i ^ 1].val += tmp;
      cur -= tmp, rec += tmp;
    }
  }
  return rec;
}
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> arr[i];
  }
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    f[i] = 1;
    for (int j = 1; j < i; j++) {
      if (arr[i] >= arr[j]) {
        f[i] = max (f[i], f[j] + 1);
      }
    }
    ans = max (ans, f[i]);
  }
  if (ans == 1) {
    cout << 1 << '\n' << n << '\n' << n << '\n';
    return 0;
  }
  cout << ans << '\n';
  S = n + n + 1, T = S + 1;
  for (int i = 1; i <= n; i++) {
    add (i, i + n, 1);
    if (f[i] == 1) {
      add (S, i, 1);
    }
    if (f[i] == ans) {
      add (i + n, T, 1);
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j < i; j++) {
      if (arr[j] <= arr[i] && f[j] + 1 == f[i]) {
        add (j + n, i, 1);
      }
    }
  }
  maxflow = 0;
  while (BFS ()) {
    maxflow += DFS (S, kInf);
  }
  cout << maxflow << '\n', maxflow = 0;
  memset (head, 0, sizeof (head)), tot = 1;
  for (int i = 1; i <= n; i++) {
    if ((i ^ 1) && (i ^ n)) {
      add (i, i + n, 1);
    } else {
      add (i, i + n, n);
    }
    if (f[i] == 1) {
      if (i ^ 1) {
        add (S, i, 1);
      } else {
        add (S, i, n);
      }
    }
    if (f[i] == ans) {
      if (i ^ n) {
        add (i + n, T, 1);
      } else {
        add (i + n, T, n);
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j < i; j++) {
      if (arr[j] <= arr[i] && f[j] + 1 == f[i]) {
        add (j + n, i, 1);
      }
    }
  }
  while (BFS ()) {
    maxflow += DFS (S, kInf);
  }
  cout << maxflow << '\n';
  return 0;
}