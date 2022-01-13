#include <bits/stdc++.h>

using namespace std;

/*Const Variable*/
const int maxn = 5e5 + 5;

/*FHQ-Treap*/
/*The Struction OF FHQ-Treap*/
struct node {
  int l, r, size, priority, v;
} tree[maxn * 50];
/*The Variable OR Array OF FHQ-Treap*/
int cnt, rt[maxn];

/*Update AND AddNode*/
inline void Update(int k) { tree[k].size = tree[tree[k].l].size + tree[tree[k].r].size + 1; }
inline void NewNode(int &k, int x) {
  tree[k = ++cnt].v = x;
  tree[k].size = 1, tree[k].priority = rand();
}

/*Merge AND Split*/
int Merge(int a, int b) {
  if (!a || !b) return a + b;

  if (tree[a].priority > tree[b].priority) {
    register int p = ++cnt;
    tree[p] = tree[a];
    tree[p].r = Merge(tree[p].r, b), Update(p);
    return p;
  } else {
    register int p = ++cnt;
    tree[p] = tree[b];
    tree[p].l = Merge(a, tree[p].l), Update(p);
    return p;
  }
}
void Split(int now, int k, int &x, int &y) {
  if (!now)
    x = y = 0;
  else if (tree[now].v <= k)
    x = ++cnt, tree[x] = tree[now], Split(tree[x].r, k, tree[x].r, y), Update(x);
  else
    y = ++cnt, tree[y] = tree[now], Split(tree[y].l, k, x, tree[y].l), Update(y);
}

/*Delete AND Insert*/
inline void Delete(int &root, int w) {
  register int x = 0, y = 0, z = 0;
  Split(root, w, x, z), Split(x, w - 1, x, y);
  y = Merge(tree[y].l, tree[y].r), root = Merge(Merge(x, y), z);
}
inline void Insert(int &root, int w) {
  register int x = 0, y = 0, z = 0;
  Split(root, w, x, y), NewNode(z, w), root = Merge(Merge(x, z), y);
}

/*Know Kth Find The Value OR Know The Value Find The Kth*/
int GetVal(int k, int w) {
  if (w == tree[tree[k].l].size + 1)
    return tree[k].v;
  else if (w <= tree[tree[k].l].size)
    return GetVal(tree[k].l, w);
  else
    return GetVal(tree[k].r, w - tree[tree[k].l].size - 1);
}
int GetKth(int &root, int w) {
  register int x, y;
  Split(root, w - 1, x, y);
  register int ans = tree[x].size + 1;
  root = Merge(x, y);
  return ans;
}

/*Get The Variable pre OR post The *root*/
inline int GetPre(int &root, int w) {
  register int x, y, k, ans;
  Split(root, w - 1, x, y);
  if (!x) return -2147483647;
  k = tree[x].size, ans = GetVal(x, k), root = Merge(x, y);
  return ans;
}
inline int GetPost(int &root, int w) {
  register int x, y, ans;
  Split(root, w, x, y);
  if (!y)
    return 2147483647;
  else
    ans = GetVal(y, 1);
  root = Merge(x, y);
  return ans;
}

/*The MAIN CODE*/
int main() {
  register int n, opt, val, VN;
  scanf("%d", &n);

  for (register int i = 1; i <= n; i++) {
    scanf("%d %d %d", &VN, &opt, &val), rt[i] = rt[VN];

    if (opt == 1)
      Insert(rt[i], val);
    else if (opt == 2)
      Delete(rt[i], val);
    else if (opt == 3)
      printf("%d\n", GetKth(rt[i], val));
    else if (opt == 4)
      printf("%d\n", GetVal(rt[i], val));
    else if (opt == 5)
      printf("%d\n", GetPre(rt[i], val));
    else
      printf("%d\n", GetPost(rt[i], val));
  }

  return 0;
}