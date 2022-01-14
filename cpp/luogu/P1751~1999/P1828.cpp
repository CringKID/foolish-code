#include <bits/stdc++.h>
using namespace std;
int cnt, n, m, vis[850], a, b, dis[850], nex[3000], fst[850], v[3000], w[3000], f[850], sum[850], c, cow, ww, mi = 1e8, ans;
void dijkstra(int k, int bei) {
  memset(dis, 0x7f / 3, sizeof(dis));
  memset(vis, 0, sizeof(vis));
  dis[k] = 0;
  int minn, t = 0;
  for (register int i = 1; i <= n; i++) {
    minn = 1e8;
    for (int j = 1; j <= n; j++)
      if (!vis[j] && dis[j] < minn) {
        minn = dis[j];
        t = j;
      }
    vis[t] = 1;
    for (register int j = fst[t]; j; j = nex[j])
      dis[v[j]] = min(dis[v[j]], dis[t] + w[j]);
  }
  for (register int i = 1; i <= n; i++) sum[i] += dis[i] * bei;
  return;
}
int main() {
  scanf("%d %d %d", &cow, &n, &m);
  for (register int i = 1; i <= cow; i++) {
    scanf("%d", &c);
    f[c]++;
  }
  for (register int i = 1; i <= m; i++) {
    scanf("%d %d %d", &a, &b, &ww);
    nex[++cnt] = fst[a];
    fst[a] = cnt;
    v[cnt] = b;
    w[cnt] = ww;
    nex[++cnt] = fst[b];
    fst[b] = cnt;
    v[cnt] = a;
    w[cnt] = ww;
  }
  for (register int i = 1; i <= n; i++)
    if (f[i]) dijkstra(i, f[i]);
  for (register int i = 1; i <= n; i++)
    if (sum[i] < mi) mi = sum[i];
  cout << mi;
  return 0;
}