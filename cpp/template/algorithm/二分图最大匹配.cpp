#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e3 + 5;

int n, m, t, Pos[maxn], Cnt[maxn];
vector<int> V[maxn];

bool DFS(int Now, int Tag) {
  if (Cnt[Now] == Tag) return false;
  Cnt[Now] = Tag;
  for (auto To : V[Now])
    if (!Pos[To] || DFS(Pos[To], Tag)) return (Pos[To] = Now);

  return false;
}

int main() {
  scanf("%d %d %d", &n, &m, &t);
  for (int i = 1, From, To; i <= t; i++) scanf("%d %d", &From, &To), V[From].push_back(To);

  int Ans = 0;
  for (int i = 1; i <= n; i++)
    if (DFS(i, i)) Ans++;

  return printf("%d\n", Ans) & 0;
}