#include <iostream>
#include <algorithm>
#include <cstring>
#include <climits>
#include <queue>

using namespace std;
using ll = long long;
const int kMaxN = 1e5 + 5, kMaxM = 3e5 + 5, kInf = INT_MAX;

int n, m, f, s, p, N, u[kMaxM], v[kMaxM], fir[kMaxM], nex[kMaxM], day[kMaxN], deg[kMaxN], en, top = -1, pre[kMaxN], pos[kMaxN];
ll r[kMaxN], flow[kMaxM], size[kMaxM], pay[kMaxM], dis[kMaxN], ans;
queue <int> que;
bool vis[kMaxN];
void add (int a, int b, ll c, int d) {
  u[++top] = a, v[top] = b, size[top] = c, flow[top] = 0, pay[top] = d, nex[top] = fir[a], fir[a] = top;
  u[++top] = b, v[top] = a, size[top] = 0, flow[top] = 0, pay[top] = -d, nex[top] = fir[b], fir[b] = top;
}
bool SPFA () {
  que.push (0);
  memset (vis, 0, sizeof (vis));
  for (int i = 1; i <= en; i++) {
    dis[i] = 1ll * kInf;
  }
  vis[0] = 1, dis[0] = 0;
  while (que.size ()) {
    int now = que.front (); que.pop (), vis[now] = false;
    for (int j = fir[now]; j != -1; j = nex[j]) {
      int to = v[j];
      if (dis[to] > dis[now] + pay[j] && size[j] > flow[j]) {
        dis[to] = dis[now] + pay[j], pre[to] = now, pos[to] = j;
        if (!vis[to]) {
          que.push (to);
          vis[to] = true;
        }
      }
    }
  }
  return dis[en] != 1ll * kInf;
}
void solve () {
  while (SPFA ()) {
    ll mmin = kInf;
    for (int i = en; i != 0; i = pre[i]) {
      mmin = min (1ll * mmin, size[pos[i]] - flow[pos[i]]);
    }
    ans += mmin * dis[en];
    for (int i = en; i != 0; i = pre[i]) {
      flow[pos[i]] += mmin;
      flow[pos[i] ^ 1] -= mmin;
    }
  }
}
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  memset (fir, -1, sizeof (fir));
  cin >> N;
  for (int i = 1; i <= N; i++) {
    cin >> r[i];
  }
  cin >> p >> m >> f >> n >> s;
  for (int i = 1; i <= N; i++) {
    day[i] = ++en, deg[i] = ++en;
  }
  en++;
  for (int i = 1; i <= N; i++) {
    add (0, day[i], kInf, p);
    add (day[i], en, r[i], 0);
    add (0, deg[i], r[i], 0);
    if (i + 1 <= N) {
      add (deg[i], deg[i + 1], kInf, 0);
    }
    if (i + m <= N) {
      add (deg[i], day[i + m], kInf, f);
    }q
    if (i + n <= N) {
      add (deg[i], day[i + n], kInf, s);
    }
  }
  solve ();
  cout << ans << '\n';
  return 0;
}