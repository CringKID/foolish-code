#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;
using Pii = pair <int, int>;
using Pll = pair <ll, ll>;
const int kMaxN = 1e6 + 5, kMod = 1e9 + 7, kInf = 1e9;

float arr[kMaxN];
int n, m, s, tot, head[kMaxN], to[kMaxN], nxt[kMaxN], edge[kMaxN], From[kMaxN], To[kMaxN], Val[kMaxN];
void add (int from, int to_, int val) {
  to[++tot] = to, edge[tot] = val;
  nxt[tot] = head[from], head[from] = tot;
}
int dfn[kMaxN], num, low[kMaxN], top, status[kMaxN], cnt;
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

   
  return 0;
}