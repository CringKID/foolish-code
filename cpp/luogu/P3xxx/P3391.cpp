#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
using ll = long long;
using Pii = pair <int, int>;
using Pll = pair <ll, ll>;
const int kMaxN = 1e5 + 5, kMod = 1e9 + 7, kInf = 1e9;

struct Node {
  int son[2], value, size, rotate;
} tr[kMaxN];
int n, m, r = 1, x, y, target;
vector <int> ve;
void Pushup (int x) {
  tr[x].size = tr[tr[x].son[0]].size + tr[tr[x].son[1]].size + (x != 0);
}
void Checkrotate (int x) {
  if (tr[x].rotate) { 
    tr[tr[x].son[0]].rotate ^= 1, tr[tr[x].son[1]].rotate ^= 1;
    swap (tr[x].son[0], tr[x].son[1]);
    tr[x].rotate = 0;
  }
}
void Rotate (int &x, bool tag) {
  int son = tr[x].son[tag];
  tr[x].son[tag] = tr[son].son[!tag], tr[son].son[!tag] = x;
  Pushup (x), Pushup (son), x = son;
}
void Balance (int &x, bool tag) {
  ve.push_back (tag);
  if (ve.size () != 2 && x != target) {
    return ;
  }
  if (ve.size () == 2) {
    Rotate (ve[0] == ve[1] ? x : tr[x].son[ve[1]], ve[0]);
  }
  Rotate (x, ve.back ());
  ve.clear ();
} 

void Rankfind (int &x, int rank) {
  Checkrotate (x);
  int now = tr[tr[x].son[0]].size + 1;
  if (rank != now) {
    bool tag = rank > now;
    Rankfind (tr[x].son[tag], rank -= tag * now);
    Balance (x, tag);
  }
}

void DFSprint (int sum) {
  if (!sum) {
    return ;
  }
  Checkrotate (sum);
  DFSprint (tr[sum].son[0]);
  cout << tr[sum].value << ' ';
  DFSprint (tr[sum].son[1]);
}
//#define contest
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);
#ifdef contest
  freopen (, , stdin);
  freopen (, , stdout);
#endif

  cin >> n >> m;
  for (int i = 1; i <= n + 1; i++) {
    tr[i] = {0, i + 1, i - 1, n - i + 3};
  }
  tr[n + 2].size = 1;
  for (int i = 1; i <= m; i++) {
    cin >> x >> y;
    target = r, Rankfind (r, y + 2);
    target = tr[r].son[0], Rankfind (tr[r].son[0], x);
    tr[tr[tr[r].son[0]].son[1]].rotate ^= 1;
  }
  target = r, Rankfind (r, n + 2);
  target = tr[r].son[0], Rankfind (tr[r].son[0], 1);
  DFSprint (tr[tr[r].son[0]].son[1]);
  return 0;
}