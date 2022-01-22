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
} tree[kMaxN];
int n, m, r = 1, x, y, target;
vector <int> ve;
void Pushup (int x) {
  tree[x].size = tree[tree[x].son[0]].size + tree[tree[x].son[1]].size + (x != 0);
}
void Checkrotate (int x) {
  if (tree[x].rotate) {
    tree[tree[x].son[0]].rotate ^= 1, tree[tree[x].son[1]].rotate ^= 1;
    swap (tree[x].son[0], tree[x].son[1]);
    tree[x].rotate = 0;
  }
}
void Rotate (int &x, bool tag) {
  int son = tree[x].son[tag];
  tree[x].son[tag] = tree[son].son[!tag], tree[son].son[!tag] = x;
  Pushup (x), Pushup (son), x = son;
}
void Balance (int &x, bool tag) {
  ve.push_back (tag);
  if (ve.size () != 2 && x != target) {
    return ;
  }
  if (ve.size () == 2) {
    Rotate (ve[0] == ve[1] ? x : tree[x].son[ve[1]], ve[0]);
  }
  Rotate (x, ve.back ());
  ve.clear ();
} 

void Rankfind (int &x, int rank) {
  Checkrotate (x);
  int now = tree[tree[x].son[0]].size + 1;
  if (rank != now) {
    bool tag = rank > now;
    Rankfind (tree[x].son[tag], rank -= tag * now);
    Balance (x, tag);
  }
}

void DFSprint (int sum) {
  if (!sum) {
    return ;
  }
  Checkrotate (x);
  DFSprint (tree[x].son[0]);
  cout << tree[x].value << ' ';
  DFSprint (tree[x].son[1]);
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
    tree[i] = {0, i + 1, i - 1, n - i + 3};
  }
  tree[n + 2].size = 1;
  for (int i = 1; i <= m; i++) {
    cin >> x >> y;
    target = r, Rankfind (r, y + 2);
    target = tree[r].son[0], Rankfind (tree[r].son[0], x);
    // cout << target << ' ';
    tree[tree[tree[r].son[0]].son[1]].rotate ^= 1;
  }
  target = r, Rankfind (r, n + 2);
  target = tree[r].son[1], Rankfind (tree[r].son[0], 1);
  DFSprint (tree[tree[r].son[0]].son[1]);
  return 0;
}