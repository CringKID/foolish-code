#include <bits/stdc++.h>

using namespace std;

const int maxn = 5e3 + 5;

struct line {
  int b, e, t;
} Line[maxn];
int n, m, ans;
bool vis[maxn * 6];

int main() {
  scanf("%d %d", &n, &m);
  for (int i = 1; i <= m; i++) scanf("%d %d %d", &Line[i].b, &Line[i].e, &Line[i].t);

  sort(Line + 1, Line + m + 1, [](line x, line y) { return x.e < y.e; });

  for (int i = 1, Reg = 0; i <= m; i++, Reg = 0) {
    for (int j = Line[i].b; j <= Line[i].e; j++)
      if (vis[j]) Reg++;
    if (Reg >= Line[i].t) continue;

    for (int j = Line[i].e; j >= Line[i].b; j--)
      if (!vis[j]) {
        vis[j] = 1, Reg++, ans++;
        if (Reg == Line[i].t) break;
      }
  }

  return printf("%d\n", ans) & 0;
}