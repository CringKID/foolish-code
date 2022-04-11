#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#define _ 0
#define LL long long
inline LL in() {
  LL x = 0, f = 1;
  char ch;
  while (!isdigit(ch = getchar())) (ch == '-') && (f = -f);
  while (isdigit(ch)) x = x * 10 + (ch ^ 48), ch = getchar();
  return x * f;
}
const int inf = 0x7fffffff;
int n, v, s, t, cnt = 1;
std::queue<int> q;
struct node {
  int to, dis, nxt, can;
  node(int to = 0, int dis = 0, int nxt = 0, int can = 0) : to(to), dis(dis), nxt(nxt), can(can) {}
} e[1050500];
int dis[1200], change[1200], head[1200], road[1200];
bool vis[1200], flag;
std::map<std::string, int> Map;
std::string str[1200], str1, str2;
int arr1[1200], arr2[1200];
int nhead[1200], sta[1200], top;
inline void add(int from, int to, int dis, int can) {
  e[++cnt] = node(to, dis, head[from], can);
  head[from] = cnt;
}
inline void link(int from, int to, int dis, int can) {
  add(from, to, dis, can);
  add(to, from, -dis, 0);
}
inline bool spfa() {
  for (int i = 1; i <= n << 1; i++) dis[i] = -inf, change[i] = inf;
  dis[s] = 0;
  q.push(s);
  while (!q.empty()) {
    int tp = q.front();
    q.pop();
    vis[tp] = false;
    for (int i = head[tp]; i; i = e[i].nxt) {
      int go = e[i].to;
      if (dis[go] < dis[tp] + e[i].dis && e[i].can > 0) {
        dis[go] = dis[tp] + e[i].dis;
        change[go] = std::min(change[tp], e[i].can);
        road[go] = i;
        if (!vis[go]) vis[go] = true, q.push(go);
      }
    }
  }
  return change[t] != inf;
}
inline void add(int from, int to) {
  e[++cnt] = node(to, 0, nhead[from], 0);
  nhead[from] = cnt;
}
inline void dfs(int x) {
  sta[++top] = x;
  vis[x] = 1;
  for (int i = nhead[x]; i; i = e[i].nxt) {
    int go = e[i].to;
    if (!vis[go]) dfs(go);
  }
}
inline void mcmf() {
  int flow = 0;
  int cost = 0;
  while (spfa()) {
    flow += change[t];
    cost += change[t] * dis[t];
    std :: cerr << change[t] << ' ' << dis[t] << '\n';
    for (int i = t; i != s; i = e[road[i] ^ 1].to) {
      e[road[i]].can -= change[t];
      e[road[i] ^ 1].can += change[t];
    }
  }
  if (cost == 2) {
    printf("2\n");
    std::cout << str[1] << '\n'
              << str[n] << '\n'
              << str[1];
  } else if (flow == 2) {
    printf("%d\n", cost);
    for (int i = 1; i <= v; i++)
      for (int j = head[arr1[i] + n]; j; j = e[j].nxt)
        if (e[j].to == arr2[i] && !e[j].can)
          add(arr1[i], arr2[i]), add(arr2[i], arr1[i]);
    dfs(s);
    for (int i = 1; i <= top; i++) std::cout << str[sta[i]] << '\n';
    std::cout << str[1];
  } else
    return (void)(printf("No Solution!"));
}
int main() {
  n = in(), v = in();
  s = 1, t = n * 2;
  for (int i = 1; i <= n; i++) {
    std::cin >> str[i];
    Map[str[i]] = i;
    link(i, i + n, 1, 1);
  }
  link(s, s + n, 0, 1);
  link(n, n + n, 0, 1);
  for (int i = 1; i <= v; i++) {
    std::cin >> str1 >> str2;
    if (Map[str1] > Map[str2]) std::swap(str1, str2);
    arr1[i] = Map[str1], arr2[i] = Map[str2];
    link(Map[str1] + n, Map[str2], 0, 1);
  }
  mcmf();
  return 0;
}