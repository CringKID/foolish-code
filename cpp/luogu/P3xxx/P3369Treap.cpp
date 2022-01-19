#include <iostream>
#include <algorithm>
#include <ctime>

using namespace std;
using ll = long long;
using Pii = pair <int, int>;
using Pll = pair <ll, ll>;
const int kMaxN = 1e5 + 5, kMod = 1e9 + 7, kInf = 1e9;

struct Node {
  int value, size, key, son[2];
} tree[kMaxN];
int n, tot, query, got, cur;
void Pushup (int now) {
  if (now) {
    tree[now].size = tree[tree[now].son[0]].size + tree[tree[now].son[1]].size + 1;
  }
}
void swap (int &x, int &y) {x ^= y ^= x ^= y;}

enum rtype { zig, zag };
void rotate (int &now, rtype need) {
  swap (tree[now].son[need == zig], tree[query].son[need == zag]);
  Pushup (now), Pushup (query);
  now = query;
}
void Balance (int &now) {
  for (int i = 0; i <= 1; i++) {
    if (tree[now].son[i] && tree[tree[now].son[i]].key < tree[now].key) {
      rotate (now, (!i ? zag : zig));
    }
  }
}

void Insert (int &now) {
  if (!now) {
    now = ++tot, tree[now].value = query, tree[now].key = rand ();
  } else {
    Insert (tree[now].son[query >= tree[now].value]);
  }
  Pushup (now), Balance (now);
}
int Replace (int &now) {
  int save = -1;
  if (!tree[now].son[1]) {
    save = tree[now].value, now = tree[now].son[0] + tree[now].son[1];
  } else {
    save = Replace (tree[now].son[1]);
  }
  return Pushup (now), save;
}
void Delete (int &now) {
  if (!now) {return ;}
  if (query == tree[now].value) {
    if (!tree[now].son[0] || !tree[now].son[1]) {
      now = tree[now].son[0] + tree[now].son[1];
    } else {
      tree[now].value = Replace (tree[now].son[0]);
    }
  } else {
    Delete (tree[now].son[query >= tree[now].value]);
  }
  Pushup (now);
}

int Lower (int now) {
  return (!now ? 0 : (tree[now].value >= query ? Lower (tree[now].son[0]) : Lower (tree[now].son[1]) + tree[tree[now].son[0]].size + 1));
}
int Rankfind (int now) {
  return Lower (now) + 1;
}
int Findrank (int now, int query) {
  int save = tree[tree[now].son[0]].size;
  return (query == save + 1 ? tree[now].value : (query <= save ? Findrank (tree[now].son[0], query) : Findrank (tree[now].son[1], query - save - 1)));
}
int Findpre () {
  int save = kInf;
  for (int now = cur; now; now = tree[now].son[tree[now].value < query]) {
    if (tree[now].value < query) {
      save = tree[now].value;
    }
  }
  return save;
}
int Findnext () {
  int save = -kInf;
  for (int now = cur; now; now = tree[now].son[tree[now].value <= query]) {
    if (tree[now].value > query) {
      save = tree[now].value;
    }
  }
  return save;
}

#define ONLINE_JUDGE
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);
#ifndef ONLINE_JUDGE
  freopen (, , stdin);
  freopen (, , stdout);
#endif
  srand (unsigned (time (0)));

  cin >> n;
  for (int i = 1, opt; i <= n; i++) {
    cin >> opt >> query;
    if (opt == 1) {
      Insert (cur);
    } else if (opt == 2) {
      Delete (cur);
    } else if (opt == 3) {
      cout << Rankfind (cur) << '\n';
    } else if (opt == 4) {
      cout << Findrank (cur, query) << '\n';
    } else if (opt == 5) {
      cout << Findpre () << '\n';
    } else {
      cout << Findnext () << '\n';
    }
  }
  return 0;
}