#include <bits/stdc++.h>
using namespace std;
struct node {
  int son[2], size, times, rd, val;
} tree[1000000];
int root, size, m, ans;
void update(int k) {
  tree[k].size = tree[tree[k].son[0]].size + tree[tree[k].son[1]].size + tree[k].times;
  return;
}
void zag(int &k) {
  int rson = tree[k].son[1];
  tree[k].son[1] = tree[rson].son[0];
  tree[rson].son[0] = k;
  tree[rson].size = tree[k].size;
  update(k);
  k = rson;
}
void zig(int &k) {
  int lson = tree[k].son[0];
  tree[k].son[0] = tree[lson].son[1];
  tree[lson].son[1] = k;
  tree[lson].size = tree[k].size;
  update(k);
  k = lson;
}
void insert(int &k, int x) {
  if (k == 0) {
    size++;
    k = size;
    tree[k].size = 1;
    tree[k].times = 1;
    tree[k].val = x;
    tree[k].rd = rand();
    return;
  }
  tree[k].size++;
  if (tree[k].val == x) {
    tree[k].times++;
    return;
  }
  if (tree[k].val < x) {
    insert(tree[k].son[1], x);
    if (tree[tree[k].son[1]].rd < tree[k].rd) zag(k);
  }
  if (tree[k].val > x) {
    insert(tree[k].son[0], x);
    if (tree[tree[k].son[0]].rd < tree[k].rd) zig(k);
  }
}
void del(int &k, int x) {
  if (tree[k].val == x) {
    if (tree[k].times > 1) {
      tree[k].times--;
      tree[k].size--;
      return;
    }
    if (tree[k].son[0] * tree[k].son[1] == 0)
      k = tree[k].son[0] + tree[k].son[1];
    else if (tree[tree[k].son[0]].rd < tree[tree[k].son[1]].rd) {
      zig(k);
      del(k, x);
    } else {
      zag(k);
      del(k, x);
    }
  } else if (tree[k].val > x) {
    tree[k].size--;
    del(tree[k].son[0], x);
  } else {
    tree[k].size--;
    del(tree[k].son[1], x);
  }
}
int ph1(int &k, int x) {
  if (k == 0) return 0;
  if (tree[k].val == x) return tree[tree[k].son[0]].size + 1;
  if (tree[k].val < x) return tree[tree[k].son[0]].size + tree[k].times + ph1(tree[k].son[1], x);
  if (tree[k].val > x) return ph1(tree[k].son[0], x);
}
int ph2(int &k, int x) {
  if (x <= tree[tree[k].son[0]].size)
    return ph2(tree[k].son[0], x);
  if (x > tree[tree[k].son[0]].size + tree[k].times) return ph2(tree[k].son[1], x - tree[tree[k].son[0]].size - tree[k].times);
  return tree[k].val;
}
void min_max(int &k, int x) {
  if (k == 0) return;
  if (tree[k].val < x) {
    ans = k;
    min_max(tree[k].son[1], x);
  } else
    min_max(tree[k].son[0], x);
}
void max_min(int &k, int x) {
  if (k == 0) return;
  if (tree[k].val > x) {
    ans = k;
    max_min(tree[k].son[0], x);
  } else
    max_min(tree[k].son[1], x);
}
int main() {
  int f, x;
  scanf("%d", &m);
  for (int i = 1; i <= m; i++) {
    scanf("%d %d", &f, &x);
    ans = 0;
    if (f == 1)
      insert(root, x);
    else if (f == 2)
      del(root, x);
    else if (f == 3)
      printf("%d\n", ph1(root, x));
    else if (f == 4)
      printf("%d\n", ph2(root, x));
    else if (f == 5) {
      min_max(root, x);
      printf("%d\n", tree[ans].val);
    } else if (f == 6) {
      max_min(root, x);
      printf("%d\n", tree[ans].val);
    }
  }
  return 0;
}