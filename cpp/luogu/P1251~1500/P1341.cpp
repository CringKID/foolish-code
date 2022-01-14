#include <algorithm>
#include <iostream>

using namespace std;
using ll = long long;
using Pii = pair<int, int>;
using Pll = pair<ll, ll>;
const int kSize = 125, kMod = 1e9 + 7, kInf = 1e9;

char ans[kSize + 5];
bool flag[kSize + 5][kSize + 5];
int n, deg[kSize + 5], first, cnt, cur = kSize;
void DFS(int now) {
  for (int i = 1; i <= kSize; i++) {
    if (flag[now][i]) {
      flag[now][i] = flag[i][now] = false;
      DFS(i);
    }
  }
  ans[n--] = now;
}
int main() {
  ios ::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);

  cin >> n;
  for (int i = 1; i <= n; i++) {
    char from, to;
    cin >> from >> to;
    flag[from][to] = flag[to][from] = true;
    deg[from]++, deg[to]++;
    cur = min(cur, int(min(from, to)));
  }
  for (int i = kSize; i > 1; i--) {
    if (deg[i] & 1) {
      cnt++;
      first = i;
    }
  }
  if (cnt == 2) {
    DFS(first);
  } else if (!cnt) {
    DFS(cur);
  } else {
    cout << "No Solution" << '\n';
    return 0;
  }
  cout << ans << '\n';
  return 0;
}