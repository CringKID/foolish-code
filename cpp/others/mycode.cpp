#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 0x3f3f3f3f;
const int N = 505;
int mp[N][N], lx[N], ly[N], visx[N], visy[N], match[N];
int n, m, minz, k;

bool dfs(int x, int K) {
  visx[x] = K;
  for (int y = 1; y <= n; ++y) {
    if (visy[y] != K && mp[x][y] != INF) {
      int t = lx[x] + ly[y] - mp[x][y];
      if (!t) {
        visy[y] = K;
        if (!match[y] || dfs(match[y], K)) {
          match[y] = x;
          return true;
        }
      } else
        minz = min(minz, t);
    }
  }
  return false;
}
void KM() {
  for (int i = 1; i <= n; ++i) {
    while (1) {
      minz = INF;
      if (dfs(i, ++k)) break;
      for (int j = 1; j <= n; ++j) {
        if (visx[j] == k) lx[j] -= minz;
        if (visy[j] == k) ly[j] += minz;
      }
    }
  }
}
int main() {
  scanf("%d%d", &n, &m);
  memset(mp, INF, sizeof mp);
  for (int i = 1; i <= n; ++i) lx[i] = -INF;
  for (int i = 0; i < m; ++i) {
    int u, v, w;
    scanf("%d%d%d", &u, &v, &w);
    mp[u][v] = w;
    lx[u] = max(lx[u], w);
  }
  KM();
  ll ans = 0;
  for (int i = 1; i <= n; ++i) ans += mp[match[i]][i];
  printf("%lld\n", ans);
  for (int i = 1; i <= n; ++i) printf("%d ", match[i]);
  putchar('\n');
  return 0;
}
