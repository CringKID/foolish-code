#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5 + 5;
typedef long long ll;
const ll inf = 0x7fffffffffffffff;

int Prime[25] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 57}, Num, Tot;
ll Array1[maxn], Ans, n, Array2[maxn], Max;

void DFS(ll Arr, int Depth, ll Temp, int Number) {
  if (Depth >= 17) return;
  if (Number > Num) Num = Number, Ans = Temp;
  if (Number == Num && Ans > Temp) Ans = Temp;

  for (int i = 1; i <= 100; i++) {
    if (Temp > Arr / Prime[Depth]) break;
    DFS(Arr, Depth + 1, Temp *= Prime[Depth], Number * (i + 1));
  }
}
void Solve(ll Now) {
  int Left = 1, Right = Tot, Mid = Left + Right >> 1;
  while (Left != Right) {
    if (Array2[Mid] > Now)
      Left = Mid + 1;
    else
      Right = Mid;
    Mid = Left + Right >> 1;
  }

  while (Array2[Mid - 1] < Now && Array2[Mid - 1]) Mid--;
  while (Array2[Mid] > Now) Mid++;
  printf("%lld\n", Array2[Mid]);
}

int main() {
  scanf("%lld", &n);
  for (int i = 1; i <= n; i++) scanf("%lld", &Array1[i]), Max = max(Max, Array1[i]);

  while (Max != 1) Ans = inf, Num = 0, DFS(Max, 0, 1, 1), Array2[++Tot] = Ans, Max = Ans - 1;
  for (int i = 1; i <= n; i++) Solve(Array1[i]);

  return 0;
}