#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
using ll = long long;
using Pii = pair <int, int>;
using Pll = pair <ll, ll>;
const int kMaxN = 4e4 + 5, kMod = 1e9 + 7, kInf = 1e9;

int n, m, head[kMaxN], tot;
bool visit[kMaxN];
struct Edge {
  int to, next;
} edge[kMaxN << 5];
void add (int from, int to) {
  edge[++tot].next = head[from];
  head[from] = tot;
  edge[tot].to = to;
}
void DFS (int now) {
  visit[now] = true;
  for (int i = head[now]; i; i = edge[i].next) {
    int to = edge[i].to;
    if (!visit[to]) {
      DFS (to);
    }
  }
}

int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    int cur;
    cin >> cur;
    for (int j = 1; j <= cur; j++) {
      int tmp;
      cin >> tmp;
      add (i, tmp + n), add (tmp + n, i);
    }
  }
  int ans = 0;
  memset (visit, false, sizeof (visit));
  for (int i = 1; i <= n; i++) {
    if (!visit[i]) {
      DFS (i);
      ans++;
    }
  }
  cout << ans - 1 << '\n';
  return 0;
}