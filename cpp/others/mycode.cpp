#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#define ll long long
using namespace std;

const int N = 100000 + 10;

inline int read() {
  int res = 0;
  char ch = getchar();
  while (ch < '0' || ch > '9') ch = getchar();
  while (ch >= '0' && ch <= '9') res = (res << 1) + (res << 3) + (ch ^ 48), ch = getchar();
  return res;
}

int a[N];

ll sum[N], t[N << 2], lazy[N << 2];
#define lson pos << 1
#define rson pos << 1 | 1
#define mid ((l + r) >> 1)
void pushdown(int pos, int l, int r) {
  lazy[lson] += lazy[pos], lazy[rson] += lazy[pos];
  t[lson] += 1ll * (mid - l + 1) * lazy[pos], t[rson] += 1ll * (r - mid) * lazy[pos];
  lazy[pos] = 0;
}

void change(int pos, int l, int r, int L, int R, int k) {
  if (l >= L && r <= R) {
    lazy[pos] += k;
    t[pos] += 1ll * k * (r - l + 1);
    return;
  }
  if (lazy[pos])
    pushdown(pos, l, r);
  if (L <= mid)
    change(lson, l, mid, L, R, k);
  if (R > mid)
    change(rson, mid + 1, r, L, R, k);
  t[pos] = t[lson] + t[rson];
}

ll query(int pos, int l, int r, int L, int R) {
  if (l >= L && r <= R)
    return t[pos];
  pushdown(pos, l, r);
  if (R <= mid)
    return query(lson, l, mid, L, R);
  else if (L > mid)
    return query(rson, mid + 1, r, L, R);
  return query(lson, l, mid, L, R) + query(rson, mid + 1, r, L, R);
}

string opt;

int main() {
  int n = read(), m = read(), x, y;
  for (int i = 1; i <= n; i++)
    a[i] = read(), sum[i] = a[i] + sum[i - 1];
  for (int i = 2; i <= n; i++)
    sum[i] += sum[i - 1];
  while (m--) {
    cin >> opt;
    if (opt == "Query") {
      x = read();
      printf("%lld\n", 1ll * sum[x] + query(1, 1, n, 1, x));
    }
    if (opt == "Modify") {
      x = read(), y = read();
      change(1, 1, n, x, n, y - a[x]);
      a[x] = y;
    }
  }
  return 0;
}