#include <bits/stdc++.h>
using namespace std;
struct node {
  int son[2], value;
} tree[20000005];
int n, m, v, loc, value, temp, a[1000005], root[1000005], tot, cnt;
int cpy(int from) {
  tree[++tot] = tree[from];
  return tot;
}
int newtree(int l, int r, int x) {
  x = ++tot;
  if (l == r) {
    tree[x].value = a[l];
    return tot;
  }
  int mid = (l + r) / 2;
  tree[x].son[0] = newtree(l, mid, tree[x].son[0]);
  tree[x].son[1] = newtree(mid + 1, r, tree[x].son[1]);
  return x;
}
int update(int l, int r, int now, int val, int x) {
  x = cpy(x);
  if (l == r)
    tree[x].value = val;
  else {
    int mid = (l + r) / 2;
    if (now <= mid)
      tree[x].son[0] = update(l, mid, now, val, tree[x].son[0]);
    else
      tree[x].son[1] = update(mid + 1, r, now, val, tree[x].son[1]);
  }
  return x;
}
int query(int l, int r, int x, int ph) {
  if (l == r) return tree[x].value;
  int mid = (l + r) / 2;
  if (ph <= mid)
    return query(l, mid, tree[x].son[0], ph);
  else
    return query(mid + 1, r, tree[x].son[1], ph);
}
int main() {
  scanf("%d %d", &n, &m);
  for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
  root[0] = newtree(1, n, 0);
  for (int i = 1; i <= m; i++) {
    scanf("%d %d %d", &v, &temp, &loc);
    if (temp == 1) {
      scanf("%d", &value);
      root[i] = update(1, n, loc, value, root[v]);
    } else {
      printf("%d\n", query(1, n, root[v], loc));
      root[i] = root[v];
    }
  }
  return 0;
}