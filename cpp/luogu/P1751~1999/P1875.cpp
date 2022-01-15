#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;
using Pii = pair <int, int>;
using Pll = pair <ll, ll>;
const int kMaxN = 1e3 + 5, kMod = 1e9 + 7, kInf = 2e9;

bool visit[kMaxN];
int n, dist[kMaxN], mat[kMaxN][kMaxN], cnt[kMaxN];
void dijkstra () {
  for (int i = 1; i <= n; i++) {
    int from, cur = kInf;
    for (int j = 1; j <= n; j++) {
      if (!visit[j] && dist[j] < cur) {
        from = j;
        cur = dist[j];
      }
    }
    if (cur == kInf) {
      break;
    }
    visit[from] = true;
    for (int j = 1; j <= n; j++) {
      if (!mat[from][j] || !visit[j]) {
        continue;
      }
      if (dist[mat[from][j]] > cur + dist[j]) {
        dist[mat[from][j]] = cur + dist[j];
        cnt[mat[from][j]] = cnt[from] * cnt[j];
      } else if (dist[mat[from][j]] == cur + dist[j]) {
        cnt[mat[from][j]] += cnt[from] * cnt[j];
      }
    }
  }
}
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> dist[i];
    cnt[i] = 1;
  }
  for (int from, to, dis; cin >> from >> to >> dis; ) {
    mat[from + 1][to + 1] = dis + 1;
    mat[to + 1][from + 1] = dis + 1;
  }
  dijkstra ();
  cout << dist[1] << ' ' << cnt[1] << '\n';
  return 0;
}