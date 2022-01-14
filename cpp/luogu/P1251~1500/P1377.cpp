#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5 + 5;

int n, a[maxn], s[maxn], tl[maxn], tr[maxn];

void dfs(int now) {
  if (now) printf("%d ", now), dfs(tl[now]), dfs(tr[now]);
}

int main() {
  scanf("%d", &n);
  for (register int i = 1, tmp; i <= n; i++) scanf("%d", &tmp), a[tmp] = i;

  for (register int i = 1, res = 0, top = 0; i <= n; i++) {
    res = top;

    while (res && a[s[res]] > a[i]) res--;

    if (res) tr[s[res]] = i;
    if (res < top) tl[i] = s[res + 1];

    s[top = ++res] = i;
  }

  return dfs(s[1]), 0;
}