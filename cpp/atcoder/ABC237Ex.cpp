#include <iostream>
#include <algorithm>
#include <atcoder/all>
#include <cstring>
#include <set>

using namespace std;
const int kMaxN = 555, kMaxM = 5e4 + 5, kInf = 1e9;

struct Edge {
  int to, next, val;
} edge[kMaxM << 1];
set <string> Set;
string str, sub[kMaxN];
int head[kMaxN], dep[kMaxN], cur[kMaxN], tot = 1, n, s, t, que[kMaxN], hd, tl, cnt;
void add (int from, int to, int val) {
  edge[++tot] = {to, head[from], val}, head[from] = tot;
  edge[++tot] = {from, head[to], 0}, head[to] = tot;
}
bool BFS () {
  memset (dep, -1, sizeof (dep)), memcpy (cur, head, sizeof (head));
  que[hd = tl = 1] = s, dep[s] = 0;
  while (hd <= tl) {
    int from = que[hd++];
    for (int i = head[from], to; i; i = edge[i].next) {
      to = edge[i].to;
      if (edge[i].val > 0 && dep[to] == -1) {
        que[++tl] = to, dep[to] = dep[from] + 1;
        if (to == t) {
          return true;
        }
      }
    }
  }
  return false;
}
int DFS (int x, int val) {
  if (x == t) {
    return val;
  }
  int rec = 0;
  for (int i = cur[x], to; i; i = edge[i].next) {
    to = edge[i].to, cur[x] = i;
    if (edge[i].val > 0 && dep[to] == dep[x] + 1) {
      int sum = DFS (to, min (val, edge[i].val));
      edge[i].val -= sum, edge[i ^ 1].val += sum;
      val -= sum, rec += sum;
    }
    if (!val) {
      break;
    }
  }
  (!rec ? dep[x] = -1 : 0);
  return rec;
}
int dinic () {
  int rec = 0;
  for ( ; BFS (); rec += DFS (s, kInf)) {
  }
  return rec;
}
bool palin (int i, int j) {
  for ( ; i <= j; i++, j--) {
    if (str[i] != str[j]) {
      return false;
    }
  }
  return true;
}
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> str, n = str.size ();
  for (int i = 0; i < n; i++) {
    for (int j = i; j < n; j++) {
      if (palin (i, j)) {
        string st = str.substr (i, j - i + 1);
        if (!Set.count (st)) {
          Set.insert (st), sub[++cnt] = st;
        }
      }
    }
  }
  s = cnt * 2 + 1, t = s + 1;
  for (int i = 1; i <= cnt; i++) {
    add (s, i, 1), add (i + cnt, t, 1);
  }
  for (int i = 1; i <= cnt; i++) {
    for (int j = 1; j <= cnt; j++) {
      (i != j && sub[i].find (sub[j]) != sub[i].npos ? add (j, i + cnt, 1) : void ());
    }
  }
  cout << cnt - dinic () << '\n';
  return 0;
}