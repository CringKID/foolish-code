#include <map>
#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;
using Pii = pair <int, int>;
using Pll = pair <ll, ll>;
const int kMaxN = 1e5 + 5, kMaxM = 1e7 + 5, kMod = 1e9 + 7, kInf = 1e9;

map <int, int> Map;
int m, son[kMaxN * 40][2], sum[kMaxN * 80], cnt, root;
void insert (int &root, int l, int r, int que, int value) {
  if (!root) {
    root = ++cnt;
  }
  sum[root] += value;
  if (l == r) {
    return ;
  }
  int mid = l + r >> 1;
  if (que <= mid) {
    insert (son[root][0], l, mid, que, value);
  } else {
    insert (son[root][1], mid + 1, r, que, value);
  }
}
int querysum (int root, int l, int r, int quel, int quer) {
  int mid = l + r >> 1, answ = 0;
  if (quel <= l && r <= quer) {
    return sum[root];
  }
  if (quel <= mid) {
    answ += querysum (son[root][0], l, mid, quel, quer);
  }
  if (quer > mid) {
    answ += querysum (son[root][1], mid + 1, r, quel, quer);
  }
  return answ;
}
int querykth (int root, int l, int r, int rnk) {
  int mid = l + r >> 1, save = sum[son[root][0]];
  if (l == r) {
    return l;
  }
  if (rnk <= save) {
    return querykth (son[root][0], l, mid, rnk);
  } else {
    return querykth (son[root][1], mid + 1, r, rnk - save);
  }
}
//#define contest
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);
#ifdef contest
  freopen (, , stdin);
  freopen (, , stdout);
#endif

  cin >> m;
  while (m--) {
    int opt, sum;
    cin >> opt >> sum;
    switch (opt) {
      case 1: 
        insert (root, 1, kMaxM << 1, sum + kMaxM, 1);
        Map[sum]++; break;
      case 2:
        insert (root, 1, kMaxM << 1, sum + kMaxM, -1);
        Map[sum]--; 
        if (!Map[sum]) {
          Map.erase (sum);
        } break;
      case 3:
        cout << querysum (root, 1, kMaxM << 1, 1, sum + kMaxM - 1) + 1 << '\n';
        break;
      case 4:
        cout << querykth (root, 1, kMaxM << 1, sum) - kMaxM << '\n';
        break;
      case 5:
        cout << (--Map.lower_bound (sum)) -> first << '\n';
        break;
      case 6:
        cout << (Map.upper_bound (sum)) -> first << '\n';
        break;
    }
  }
  return 0;
}