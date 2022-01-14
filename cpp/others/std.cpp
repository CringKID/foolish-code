#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
using ll = long long;
using Pii = pair <int, int>;
using Pll = pair <ll, ll>;
const int kMaxN = 1e5 + 5, kMod = 1e9 + 7, kInf = 1e9;

int n, m, cost[kMaxN], head[kMaxN], to[kMaxN << 2], nxt[kMaxN << 2], tot;
void add (int from, int to_) {
  to[++tot] = to_, nxt[tot] = head[from];
  head[from] = tot;
}
int dfn[kMaxN], low[kMaxN], mincost[kMaxN], co[kMaxN], num[kMaxN], stack[kMaxN], col = 1, maxdfn = 1, top;
void tarjan (int now) {
  dfn[now] = low[now] = maxdfn++;
  stack[top++] = now;
  for (int i = head[now]; ~i; i = nxt[i]) {
    if (!dfn[to[i]]) {
      tarjan (to[i]);
      low[now] = min (low[now], low[to[i]]);
    } else if (!co[to[i]]) {
      low[now] = min (low[now], dfn[to[i]]);
    }
  }
  if (dfn[now] == low[now]) {
    mincost[col] = cost[now], num[col] = 1;
    while (stack[--top] != now) {
      co[stack[top]] = col;
      if (cost[stack[top]] < mincost[col]) {
        mincost[col] = cost[stack[top]];
        num[col] = 1;
      } else if (cost[stack[top]] == mincost[col]) {
        num[col]++;
      }
    }
    co[now] = col++;
  }
}
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  memset (head, -1, sizeof (head));
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> cost[i];
  }
  cin >> m;
  for (int i = 1, from, to; i <= m; i++) {
    cin >> from >> to;
    add (from, to);
  }
  for (int i = 1; i <= n; i++) {
    if (!co[i]) {
      tarjan (i);
    }
  }
  ll ans = 0, sum = 1;
  for (int i = 1; i < col; i++) {
    ans += mincost[i];
    sum = sum * num[i] % kMod;
  }
  cout << ans << ' ' << sum << '\n';
  return 0;
}