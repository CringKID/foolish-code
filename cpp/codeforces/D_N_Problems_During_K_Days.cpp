#include <iostream>
#include <algorithm>
#include <vector>


using namespace std;
using ll = long long;
const ll kMaxN = 1e6 + 5, kInf = 1e10;

int cur;
vector <int> rec;
ll n, x, y, arr[kMaxN], sum[kMaxN], vis[kMaxN], l[kMaxN], r[kMaxN], flag, ans, k, t;
bool check (ll x) {
  ll p = 0;
  if (k <= cur) {
    p = x * ((1 << k) - 1);
  } else {
    p = kInf;
  }
  return n <= p;
}
ll binarysearch (ll l, ll r, ll x) {
  ll ans = 0;
  while (l <= r) {
    ll mid = l + r >> 1;
    if (check (mid)) {
      ans = mid;
      r = mid - 1;
    } else {
      l = mid + 1;
    }
  }
  return ans;
}
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  for (int i = 1; ; i++) {
    if ((1 << i) > 1e9) {
      break;
    }
    cur = i;
  }
  cin >> n >> k;
  t = binarysearch (1, n, n);
  y = (t * 2 + k - 1) * k / 2;
  if (y > n) {
    cout << "NO" << '\n';
    return 0;
  }
  ll l, r;
  rec.push_back (t);
  n -= t, t++, k--;
  while (k) {
    t = binarysearch (t, t * 2, n);
    rec.push_back (t), n -= t;
    t++, k--;
  }
  cout << "YES" << '\n';
  for (int i : rec) {
    cout << i << ' ';
  }
  return 0;
}