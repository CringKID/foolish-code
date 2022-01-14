#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e6 + 5;

int T, n, Father[maxn << 1], Pre[maxn], Next[maxn], Opt[maxn], Tot;
map<int, int> mmap, Clear;
void Clear_map() { mmap = Clear; }
int Root(int x) { return Father[x] == x ? x : Father[x] = Root(Father[x]); }

int main() {
  scanf("%d", &T);

  while (T--) {
    Tot = 0, Clear_map();
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
      scanf("%d %d %d", &Pre[i], &Next[i], &Opt[i]);
      if (!mmap[Pre[i]]) mmap[Pre[i]] = ++Tot;
      if (!mmap[Next[i]]) mmap[Next[i]] = ++Tot;
    }
    for (int i = 1; i <= Tot; i++) Father[i] = i;

    bool Flag = 1;
    for (int i = 1; i <= n; i++)
      if (Opt[i]) {
        int F1 = Root(mmap[Pre[i]]), F2 = Root(mmap[Next[i]]);
        if (F1 != F2) Father[F1] = F2;
      }
    for (int i = 1; i <= n; i++)
      if (!Opt[i]) {
        int F1 = Root(mmap[Pre[i]]), F2 = Root(mmap[Next[i]]);
        if (F1 == F2) {
          Flag = 0;
          break;
        }
      }

    puts(Flag ? "YES" : "NO");
  }

  return 0;
}