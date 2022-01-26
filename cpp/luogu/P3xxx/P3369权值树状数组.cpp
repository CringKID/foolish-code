#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;
using Pii = pair <int, int>;
using Pll = pair <ll, ll>;
const int kMaxN = 1e7 + 5, kMod = 1e9 + 7, kInf = 1e9;

int ques, opt, x, tree[kMaxN * 2];
void Update (int x, int value) {
  for (int i = x; i < kMaxN * 2; i += i & -i) {
    tree[i] += value;
  }
}
int Query (int x) {
  int total = 0;
  for (int i = x; i; i -= i & -i) {
    total += tree[i];
  }
  return total;
}
int Place (int value) {
  int cur = 0, sum = 0;
  for (int i = 25; ~i; i--) {
    cur += 1 << i;
    if (cur >= kMaxN * 2 - 1 || sum + tree[cur] >= value) {
      cur -= 1 << i;
    } else {
      sum += tree[cur];
    }
  }
  return cur + 1;
}
//#define contest
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);
#ifdef contest
  freopen (, , stdin);
  freopen (, , stdout);
#endif

  cin >> ques;
  while (ques--) {
    cin >> opt >> x;
    switch (opt) {
      case 1 :
        Update (x + kMaxN, 1);
        break;
      case 2 :
        Update (x + kMaxN, -1);
        break;
      case 3 : 
        cout << Query (x + kMaxN - 1) + 1 << '\n';
        break;
      case 4 : 
        cout << Place (x) - kMaxN << '\n';
        break;
      case 5 :
        cout << Place (Query (x + kMaxN - 1)) - kMaxN << '\n';
        break;
      default :
        cout << Place (Query (x + kMaxN) + 1) - kMaxN << '\n';
    }
  }
  return 0;
}