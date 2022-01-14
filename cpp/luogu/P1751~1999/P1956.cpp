#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5 + 5;

int n, k, mod, Ans = 1e9, Array[maxn];
set<int> Set;

int main() {
  scanf("%d %d %d", &n, &k, &mod);
  Array[0] = 0, Set.insert(0);
  for (int i = 1, Temp; i <= n; i++) scanf("%d", &Temp), Array[i] = (Array[i - 1] + Temp) % mod;

  for (int i = 1; i <= n; i++) {
    if (Array[i] >= k)
      Ans = min(Ans, Array[i] - (*--Set.upper_bound(Array[i] - k)));
    else
      Ans = min(Ans, Array[i] + mod - (*--Set.upper_bound(Array[i] - k + mod)));

    Set.insert(Array[i]);
  }

  return printf("%d\n", Ans) & 0;
}