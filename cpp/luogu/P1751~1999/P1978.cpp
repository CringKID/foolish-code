#include <bits/stdc++.h>
using namespace std;
long long a[100005];
set<long long> s;
int n, mod;
int main() {
  scanf("%d %d", &n, &mod);
  for (register int i = 1; i <= n; i++) scanf("%lld", &a[i]);
  sort(a + 1, a + n + 1);
  for (register int i = 1; i <= n; i++)
    if (a[i] % mod || s.find(a[i] / mod) == s.end()) s.insert(a[i]);
  printf("%d\n", s.size());
  return 0;
}