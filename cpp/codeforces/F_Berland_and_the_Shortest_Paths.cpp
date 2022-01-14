#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;
using ll = long long;
const int kMaxN = 2e5 + 5, kInf = 1e9;

queue <int> q;
char ch[kMaxN];
vector <string> str;
vector <int> ve[kMaxN];
int dist[kMaxN], n, m, k;
vector <pair <int, int> > edge[kMaxN];
void BFS () {
  fill (dist, dist + n + 1, kInf);
  q.push (1), dist[1] = 0;
  while (!q.empty ()) {
    int now = q.front (); q.pop ();
    for (pair <int, int> P : edge[now]) {
      int to = P.first;
      if (dist[to] > dist[now] + 1) {
        dist[to] = dist[now] + 1;
        q.push (to);
      }
    }
  }
}
void DFS (int limit, int now) {
  if ((int)str.size () >= k) {
    return ;
  }
  if (now > limit) {
    str.push_back (ch + 1);
    return ;
  }
  for (int & i : ve[now]) {
    ch[i] = '1';
    DFS (limit, now + 1);
    ch[i] = '0';
  }
}

int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n >> m >> k;
  for (int i = 1, from, to; i <= m; i++) {
    cin >> from >> to;
    edge[from].emplace_back (to, i);
    edge[to].emplace_back (from, i);
  }
  BFS ();

  for (int i = 2; i <= n; i++) {
    for (pair <int, int> P : edge[i]) {
      int from = P.first;
      if (dist[from] + 1 == dist[i]) {
        ve[i].push_back (P.second);
      }
    }
  }
  fill (ch, ch + m + 1, '0');
  DFS (n, 2);
  cout << str.size () << '\n';
  for (int i = 0; i < str.size (); i++) {
    cout << str[i] << '\n';
  }
  return 0;
}