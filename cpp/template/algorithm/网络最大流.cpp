#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e4 + 5, e = 2e5 + 5;

typedef long long ll;

int n, m, s, t, dep[maxn], q[maxn], l, r;

ll Ans = 0, cnt = 1, first[maxn], nxt[e], to[e], val[e];

inline void add(int from, int to_, int dis) { to[++cnt] = to_, val[cnt] = dis, nxt[cnt] = first[from], first[from] = cnt; }

inline bool bfs() {
  memset(dep, 0, (n + 1) * 4);

  q[l = r = 1] = s, dep[s] = 1;

  while (l <= r) {
    register int from = q[l++];

    for (register int i = first[from], to_; i; i = nxt[i]) {
      to_ = to[i];
      if (val[i] && !dep[to_]) dep[to_] = dep[from] + 1, q[++r] = to_;
    }
  }

  return dep[t];
}

ll dfs(int from, ll sum) {
  if (from == t) return sum;

  ll ans = 0;

  for (register int i = first[from], to_; i && sum; i = nxt[i]) {
    to_ = to[i];

    if (val[i] && dep[to_] == dep[from] + 1) {
      ll res = dfs(to_, min(val[i], sum));
      val[i] -= res, val[i ^ 1] += res;
      sum -= res, ans += res;
    }
  }

  if (!ans) dep[from] = 0;
  return ans;
}

int main() {
  scanf("%d %d %d %d", &n, &m, &s, &t);
  for (register int i = 1, from, to_; i <= m; i++) {
    ll dis;
    scanf("%d %d %lld", &from, &to_, &dis);
    add(from, to_, dis), add(to_, from, 0);
  }

  while (bfs()) Ans += dfs(s, 1e18);

  printf("%lld\n", Ans);

  return 0;
}