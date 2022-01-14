#include <bits/stdc++.h>
#define lowbit(x) x&(-x)
using namespace std;
const int maxn = 1e6 + 5;
int num[maxn], tree[maxn], booll[maxn], nnn[maxn], n, m;
struct Q {
  int l, r;
  int pos;
} qur[maxn];
bool cmp(Q x, Q y) {
  return x.r < y.r;
}
namespace Tree_Array {
void add(int x, int now) {
  while (x <= n) {
    tree[x] += now;
    x += lowbit(x);
  }
}
int sum(int x) {
  int ans = 0;
  while (x != 0) {
    ans += tree[x];
    x -= lowbit(x);
  }
  return ans;
}
}  // namespace Tree_Array
using namespace Tree_Array;
int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) scanf("%d", &num[i]);
  scanf("%d", &m);
  for (int i = 1; i <= m; i++) {
    scanf("%d %d", &qur[i].l, &qur[i].r);
    qur[i].pos = i;
  }
  sort(qur + 1, qur + 1 + m, cmp);
  int next = 1;
  for (register int i = 1; i <= m; i++) {
    for (register int j = next; j <= qur[i].r; j++) {
      if (booll[num[j]]) add(booll[num[j]], -1);
      add(j, 1);
      booll[num[j]] = j;
    }
    next = qur[i].r + 1;
    nnn[qur[i].pos] = sum(qur[i].r) - sum(qur[i].l - 1);
  }
  for (register int i = 1; i <= m; i++) cout << nnn[i] << endl;
  return 0;
}