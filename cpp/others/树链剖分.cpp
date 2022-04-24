#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
using ll = long long;
using Pii = pair <int, int>;
using Pll = pair <ll, ll>;
const int kMaxN = 1e5 + 5, kMod = 1e9 + 7, kInf = 1e9;



/*
Tree_Build (x, dep) 
  x.hson <- 0
  x.hson.siz <- 0
  x.deep <- dep
  x.siz <- 1
  for each y in x.son 
    x.siz <- x.siz + Tree_Build (y, dep + 1)
    y.fath <- x;
    if y.siz > x.hson.siz 
      x.hson <- y;
  return x.siz
Tree_Decomposition (x, top) 
  x.top <- top
  tot <- tot + 1
  x.dfn <- tot
  tot.rnk <- x
  if x.hson is not 0
    Tree_Decomposition (x.hson, top)
    for each y in x.son
      if y is not x.hson 
        Tree_Decomposition (y, y)
*/
int rnk[kMaxN], top[kMaxN];
struct Node {
  int hson, siz, dep, fath, dfn;
} tree[kMaxN];
vector <int> edge[kMaxN];
int DFS1 (int x, int dep) {
  tree[x].hson = 0, tree[tree[x].hson].siz = 0;
  tree[x].dep = dep, tree[x].siz = 1;
  for (int y : edge[x]) {
    tree[x].siz = tree[x].siz + DFS1 (y, dep + 1);
    tree[y].fath = x;
    if (tree[y].siz > tree[tree[x].hson].siz) {
      tree[x].hson = y;
    }
  }
  return tree[x].siz;
}




//#define contest
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);
#ifdef contest
  freopen (, , stdin);
  freopen (, , stdout);
#endif

  
  return 0;
}