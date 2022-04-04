#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#define INF 0x3f3f3f3f

using namespace std;

const int N = 300 + 10;
const int M = 50 + 10;
struct node {
  int x, val, to, nxt, op;
} e[N * M * 2 + N + N];
int n, m, S, T, le[N + 10], tot, KK, disum;
int ru[N + 10], chu[N + 10], s1, s2, t1, t2;
int dis[N + 10], lee[N + 10], deg[N + 10];  
bool in[N + 10];

void Add(int x, int y, int z, int w) {
  e[++KK] = (node){z, w, y, le[x], KK + 1};
  le[x] = KK;
  e[++KK] = (node){0, -w, x, le[y], KK - 1};
  le[y] = KK;
}

bool SPFA() {
  memset(deg, 0x7f, sizeof(deg));
  memset(dis, 0x7f, sizeof(dis));
  memcpy(lee, le, sizeof(lee));
  deg[S] = 0;
  dis[S] = 0;
  queue<int> q;
  q.push(S);
  in[S] = 1;
  while (!q.empty()) {
    int now = q.front();
    q.pop();
    for (int i = le[now]; i; i = e[i].nxt)
      if (e[i].x && dis[e[i].to] > dis[now] + e[i].val) {
        dis[e[i].to] = dis[now] + e[i].val;
        deg[e[i].to] = deg[now] + 1;
        if (!in[e[i].to]) {
          in[e[i].to] = 1;
          q.push(e[i].to);
        }
      }
    in[now] = 0;
  }
  return dis[T] != dis[0];
}

int dfs(int now, int sum) {
  if (now == T) {
    return sum;
  }
  int rec = 0;
  for (int i = lee[now]; i; i = e[i].nxt) {
    if (e[i].x && deg[e[i].to] == deg[now] + 1 && dis[e[i].to] == dis[now] + e[i].val) {
      int to = dfs(e[i].to, min (sum - rec, e[i].x));
      if (to) {
        e[i].x -= to;
        e[e[i].op].x += to;
        rec += to;
        if (rec == sum) {
          return sum;
        }
      }
    }
  }
  if (rec != sum) {
    dis[now] = -1;
  }
  return rec;
}

int Dinic() {
  int rec = 0;
  while (SPFA()) {
    rec += dfs (S, INF) * dis[T];
  }
  return rec;
}
int main() {
  scanf("%d", &n);

  tot = n;
  s1 = 1;
  t1 = ++tot;
  s2 = ++tot;
  t2 = ++tot;
  for (int i = 1; i <= n; i++) {
    int k, b, t;
    scanf("%d", &k);
    for (int j = 1; j <= k; j++) {
      scanf("%d %d", &b, &t);
      Add(i, b, INF, t);
      chu[i] += 1;
      ru[b] += 1;
      disum += 1 * t;
    }
  }
  for (int i = 2; i <= n; i++) {
    Add(i, t1, INF, 0);
  }

  for (int i = 1; i <= n; i++) {
    if (ru[i] > chu[i]) Add(s2, i, ru[i] - chu[i], 0);
    if (chu[i] > ru[i]) Add(i, t2, chu[i] - ru[i], 0);
  }

  Add(t1, s1, INF, 0);
  S = s2;
  T = t2;
  printf("%d", disum + Dinic());

  return 0;
}