#include <bits/stdc++.h>
using namespace std;
struct node {
  int son[2], size;
} tree[5000005];
int n, m, a[200005], l, r, rk, temp[200005], tmp, root[200005], tot;
int cpy(int from) {
  tree[++tot] = tree[from];
  return tot;
}
inline int newnode() {
  tree[++tot].son[0] = 0;
  tree[tot].son[1] = 0;
  tree[tot].size = 0;
  return tot;
}
int newtree(int l, int r) {
  int num = newnode();
  if (l == r) return num;
  int mid = (l + r) / 2;
  tree[num].son[0] = newtree(l, mid);
  tree[num].son[1] = newtree(mid + 1, r);
  return num;
}
void insert(int value, int x, int l, int r) {
  tree[x].size++;
  if (l == r) return;
  int mid = (l + r) / 2;
  if (value <= mid) {
    tree[x].son[0] = cpy(tree[x].son[0]);
    insert(value, tree[x].son[0], l, mid);
  } else {
    tree[x].son[1] = cpy(tree[x].son[1]);
    insert(value, tree[x].son[1], mid + 1, r);
  }
}
int query(int l, int r, int r1, int r2, int ph) {
  if (l == r) return l;
  int mid = (l + r) / 2;
  int t = tree[tree[r2].son[0]].size - tree[tree[r1].son[0]].size;
  if (ph <= t)
    return query(l, mid, tree[r1].son[0], tree[r2].son[0], ph);
  else
    return query(mid + 1, r, tree[r1].son[1], tree[r2].son[1], ph - t);
}
int main() {
  scanf("%d %d", &n, &m);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
    temp[i] = a[i];
  }
  root[0] = newtree(1, n);
  sort(temp, temp + n);
  for (int i = 1; i <= n; i++) {
    tmp = lower_bound(temp, temp + n, a[i]) - temp;
    root[i] = cpy(root[i - 1]);
    insert(tmp, root[i], 1, n);
  }
  for (int i = 0; i < m; i++) {
    scanf("%d %d %d", &l, &r, &rk);
    printf("%d\n", temp[query(1, n, root[l - 1], root[r], rk)]);
  }
  return 0;
}