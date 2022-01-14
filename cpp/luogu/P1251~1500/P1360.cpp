#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e4 + 5;

map<vector<int>, int> mmap;

int n, m, ans;

int main() {
  scanf("%d %d", &n, &m);
  vector<int> v(m);
  mmap[v] = 0;
  for (register int i = 1, x; i <= n; i++) {
    scanf("%d", &x);
    for (register int j = 0; j < m; j++)
      if (x & (1 << j)) v[j]++;
    if (x & 1)
      for (register int j = 0; j < m; j++) v[j]--;
    if (mmap.count(v))
      ans = max(ans, i - mmap[v]);
    else
      mmap[v] = i;
  }
  printf("%d\n", ans);
  return 0;
}