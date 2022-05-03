#include <bits/stdc++.h>
using namespace std;
#include <atcoder/maxflow>
using namespace atcoder;

using ll = long long;
const ll INF = 1001001001001001001LL;

#define rep(i, l, r) for (auto i = (l); i != (r); i++)

int main() {
  int N, M;
  cin >> N >> M;
  // 入頂点を N+i 、出頂点を i としている
  mf_graph<ll> g(N * 2);

  rep(i, 0, M) {
    int a, b;
    cin >> a >> b;
    a--, b--;
    g.add_edge(N + a, b, INF);
    g.add_edge(N + b, a, INF);
  }

  vector<ll> c(N);
  rep(i, 0, N) cin >> c[i];
  c[0] = c[N - 1] = INF;

  rep(i, 0, N)
      g.add_edge(i, N + i, c[i]);

  ll mincut = g.flow(N, N - 1);  // 提出コード上では 0 から N + (N - 1) となっていますが、（一応それでも合いますが）頂点 1 の入頂点から頂点 N の出頂点へと考えるとこちらの方が正しいです
  auto reachable = g.min_cut(0);

  vector<int> ans;
  rep(i, 0, N) if (reachable[i] && !reachable[N + i])
      ans.push_back(i + 1);

  cout << mincut << endl;
  cout << ans.size() << endl;
  rep(i, 0, ans.size())
          cout
      << ans[i] << " \n"[i == ans.size() - 1];
}