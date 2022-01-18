#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;
using Pii = pair <int, int>;
using Pll = pair <ll, ll>;
const int kMaxN = 1e5 + 5, kMod = 1e9 + 7, kInf = 1e9;

string opt;
int arr[kMaxN], n, m;
ll sum[kMaxN], tree[kMaxN << 2], lazytag[kMaxN << 2];
void pushup (int rt) {
  tree[rt] = tree[rt << 1] + tree[rt << 1 | 1];
}
void pushdown (int rt, int left, int right) {
  lazytag[rt << 1] += lazytag[rt];
  lazytag[rt << 1 | 1] += lazytag[rt];
  int mid = left + right >> 1;
  tree[rt] += 1ll * (mid - left + 1) * lazytag[rt];
  tree[rt << 1 | 1] += 1ll * (right - mid) * lazytag[rt];
  lazytag[rt] = 0;
}

void update (int rt, int left, int right, int Left, int Right, int value) {
  if (left >= Left && right <= Right) {
    lazytag[rt] += value;
    return tree[rt] += 1ll * value * (right - left + 1), void ();
  }
  lazytag[rt] && (pushdown (rt, left, right), false);
  int mid = left + right >> 1;
  Left <= mid && (update (rt << 1, left, mid, Left, Right, value), false);
  right > mid && (update (rt << 1 | 1, mid + 1, right, Left, Right, value), false);
  pushup (rt);
}
ll query (int rt, int left, int right, int Left, int Right) {
  if (left >= Left && right <= Right) {
    return tree[rt];
  }
  pushdown (rt, left, right);
  int mid = left + right >> 1;
  if (Right <= mid) {
    query (rt << 1, left, mid, Left, Right);
  } else if (Left > mid) {
    query (rt << 1 | 1, mid + 1, right, Left, Right);
  }
  return query (rt << 1, left, mid, Left, Right) + query (rt << 1 | 1, mid + 1, right, Left, Right);
}

int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> arr[i];
    sum[i] = arr[i] + sum[i - 1];
  }
  for (int i = 2; i <= n; i++) {
    sum[i] += sum[i - 1];
  }
  for (int i = 1, l, r; i <= m; i++) {
    cin >> opt;
    if (opt == "Query") {
      cin >> l;
      cout << 1ll * sum[l] + query (1, 1, n, 1, l) << '\n';
    } else if (opt == "Modify") {
      cin >> l >> r;
      update (1, 1, n, l, n, r - arr[l]);
      arr[l] = r;
    }
  }
  return 0;
}