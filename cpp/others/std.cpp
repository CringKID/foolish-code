#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
using ll = long long;
using Pii = pair <int, int>;
using Pll = pair <ll, ll>;
const int kMaxN = 1e5 + 5, kMod = 1e9 + 7, kInf = 1e9;

vector <int> edge[kMaxN];
int n, m, tag1, tag2, tag, sum = 1, top, stack[kMaxN], indeg[kMaxN], outdeg[kMaxN], nxt[kMaxN];
void DFS (int now) {
  for (int i = nxt[now]; i < edge[now].size (); i = nxt[now]) {
    nxt[now] = i + 1;
    DFS (edge[now][i]);
  }
  stack[++top] = now;
}
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n >> m;
  for (int i = 1, from, to; i <= m; i++) {
    cin >> from >> to;
    edge[from].push_back (to);
    outdeg[from]++, indeg[to]++;
  }
  for (int i = 1; i <= n; i++) {
    if (indeg[i] == outdeg[i] - 1) {
      tag1++, sum = i;
    } else if (outdeg[i] == indeg[i] - 1) {
      tag2++;
    } else if (indeg[i] != outdeg[i]) {
      tag = 1;
    }
  }
  if (tag && !(tag1 == 1 && tag2 == 1)) {
    cout << "No" << '\n';
    return 0;
  }
  for (int i = 1; i <= n; i++) {
    sort (edge[i].begin (), edge[i].end ());
  }
  DFS (sum);
  for (int i = top; i >= 1; i--) {
    cout << stack[i] << ' ';
  }
  return 0;
}