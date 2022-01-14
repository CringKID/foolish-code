#include <bits/stdc++.h>

using namespace std;

const int maxn = 405;

int Head[maxn * maxn], To[maxn * maxn], Next[maxn * maxn], Tot = 1, Ans, Connect[maxn], Vis[maxn], n, T;
void Add(int from, int to) { To[++Tot] = to, Next[Tot] = Head[from], Head[from] = Tot; }

bool DFS(int Now) {
  for (int i = Head[Now], to; i; i = Next[i])
    if (!Vis[to = To[i]]) {
      Vis[to] = 1;
      if (!Connect[to] || DFS(Connect[to])) {
        Connect[to] = Now;
        return true;
      }
    }
  return false;
}
void Clear() {
  Ans = 0;
  for (int i = 1; i <= Tot; i++) To[i] = Head[i] = Next[i] = 0;
  Tot = 1;
  for (int i = 0; i <= n << 1; i++) Connect[i] = 0;
}

int main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
      for (int j = 1, Temp; j <= n; j++) {
        scanf("%d", &Temp);
        if (Temp == 1) Add(i, j + n);
      }

    for (int i = 1; i <= n; i++) {
      memset(Vis, 0, sizeof(Vis));
      if (DFS(i)) Ans++;
    }

    if (Ans >= n)
      puts("Yes");
    else
      puts("No");
    Clear();
  }

  return 0;
}