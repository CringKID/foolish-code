#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;
using Pii = pair <int, int>;
using Pll = pair <ll, ll>;
const int kMaxN = 1e5 + 5, kMod = 1e9 + 7, kInf = 1e9;

struct Node {
  int value, size, son[2];
} tree[kMaxN];
int n, tot, x, y;
void Pushup (int rt) {
  tree[rt].size = tree[tree[rt].son[0]].size + tree[tree[rt].son[1]].size + (rt != 0);
}
void Insert (int &rt) {
  if (!rt) {
    tree[rt = ++tot].value = y;
    return Pushup (rt);
  }
  Insert (y < tree[rt].value ? tree[rt].son[0] : tree[rt].son[1]);
  Pushup (rt);
}
int Replace (int &rt) {
  int save = tree[rt].value;
  if (!tree[rt].son[1]) {
    rt = tree[rt].son[0];
  } else {
    save = Replace (tree[rt].son[1]);
    Pushup (rt);
  }
  return save;
}

void Delete (int &rt) {
  if (y == tree[rt].value) {
    if (!tree[rt].son[0] || !tree[rt].son[1]) {
      rt = tree[rt].son[0] + tree[rt].son[1];
    } else {
      tree[rt].value = Replace (tree[rt].son[0]);
    }
  } else {
    Delete (y < tree[rt].value ? tree[rt].son[0] : tree[rt].son[1]);
  }
  Pushup (rt);
}
int Lower (int rt) {
  return (!rt ? 0 : (tree[rt].value >= y ? Lower (tree[rt].son[0]) : Lower (tree[rt].son[1]) + tree[tree[rt].son[0]].size + 1));
}
int Findrank (int x) {
  return Lower (x) + 1;
}
int Rankfind (int x, int y) {
  int save = tree[tree[x].son[0]].size;
  return (y == save + 1 ? tree[x].value : (y <= save ? Rankfind (tree[x].son[0], y) : Rankfind (tree[x].son[1], y - save - 1)));
}
int Findpre (int x) {
  return (!x ? -kInf : (tree[x].value < y ? max (tree[x].value, Findpre (tree[x].son[1])) : Findpre (tree[x].son[0])));
}
int Findnext (int x) {
  return (!x ? kInf : (tree[x].value > y ? min (tree[x].value, Findnext (tree[x].son[0])) : Findnext (tree[x].son[1])));
}

//#define contest
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);
#ifdef contest
  freopen (, , stdin);
  freopen (, , stdout);
#endif

  cin >> n;
  for (int i = 1, opt, sum; i <= n; i++) {
    cin >> opt >> y;
    if (opt == 1) {
      Insert (sum);
    } else if (opt == 2) {
      Delete (sum);
    } else if (opt == 3) {
      cout << Findrank (sum) + 1 << '\n';
    } else if (opt == 4) {
      cout << Rankfind (sum, y) << '\n';
    } else if (opt == 5) {
      cout << Findpre (sum) << '\n';
    } else {
      cout << Findnext (sum) << '\n';
    }
  }
  return 0;
}