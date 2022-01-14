#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e4 + 5, maxm = 3e5 + 5;
int n, m, head[maxn], tot;
map<string, int> couple;
struct people {
  int to, next;
} relation[maxm];
inline void add(int x, int y) {
  relation[++tot].to = y;
  relation[tot].next = head[x];
  head[x] = tot;
}
bool vis[maxn];
stack<int> s;
int cnt, dfn[maxn], low[maxn], belong[maxn], ncnt;
void tarjan(int x) {
  dfn[x] = low[x] = ++cnt;
  s.push(x);
  vis[x] = 1;
  for (int i = head[x]; i; i = relation[i].next) {
    int t = relation[i].to;
    if (!dfn[t]) {
      tarjan(t);
      low[x] = min(low[x], low[t]);
    } else if (vis[t])
      low[x] = min(low[x], dfn[t]);
  }
  if (low[x] == dfn[x]) {
    ncnt++;
    belong[s.top()] = ncnt;
    vis[s.top()] = 0;
    while (s.top() != x) {
      s.pop();
      belong[s.top()] = ncnt;
      vis[s.top()] = 0;
    }
    s.pop();
  }
}
string girl, boy;
int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    cin >> girl >> boy;
    couple[girl] = i;
    couple[boy] = i + n;
    add(i, i + n);
  }
  scanf("%d", &m);
  for (int i = 1; i <= m; i++) {
    cin >> girl >> boy;
    add(couple[boy], couple[girl]);
  }
  for (int i = 1; i <= 2 * n; i++)
    if (!dfn[i]) tarjan(i);
  for (int i = 1; i <= n; i++) {
    if (belong[i] == belong[i + n])
      printf("Unsafe\n");
    else
      printf("Safe\n");
  }
  return 0;
}