#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n, m, tree1[100005], tree2[100005], temp, r, l, add, pre;
ll lowbit(ll x) {
  return x & -x;
}
void update(ll x, ll y, ll tree[]) {
  while (x <= n) {
    tree[x] += y;
    x += lowbit(x);
  }
  return;
}
ll query(ll x, ll tree[]) {
  ll sum = 0;
  while (x > 0) {
    sum += tree[x];
    x -= lowbit(x);
  }
  return sum;
}
int main() {
  scanf("%lld %lld", &n, &m);
  for (ll i = 1; i <= n; i++) {
    ll x;
    scanf("%lld", &x);
    update(i, x - pre, tree1);
    update(i, i * (x - pre), tree2);
    pre = x;
  }
  for (ll i = 0; i < m; i++) {
    scanf("%lld %lld %lld", &temp, &l, &r);
    if (temp == 2) {
      ll sum = (r - l + 1) * query(r, tree1) + l * (query(r, tree1) - query(l, tree1)) + (query(r, tree2) - query(l, tree2));
      printf("%lld\n", sum);
    } else {
      scanf("%lld", &add);
      update(l, add, tree1);
      update(r + 1, -add, tree1);
      update(l, l * add, tree2);
      update(r + 1, (r + 1) * -add, tree2);
    }
  }
  return 0;
}