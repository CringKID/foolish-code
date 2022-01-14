#include <algorithm>
#include <iostream>

using namespace std;
using ll = long long;
using Pii = pair<int, int>;
using Pll = pair<ll, ll>;
const int kMaxN = 1e5 + 5, kMod = 1e9 + 7, kInf = 1e9;

bool tag;
ll n, m, tl, tr, arr[kMaxN], sum[kMaxN];
int main() {
  ios ::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);

  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    ll cur;
    cin >> cur;
    arr[i] = cur * 1000;
    tr = max(arr[i], tr);
  }
  while (tl < tr) {
    ll mid = tl + tr >> 1, mmin = 0;
    tag = false;
    for (int i = 1; i <= n; i++) {
      sum[i] = sum[i - 1] + arr[i] - mid;
      if (i >= m) {
        mmin = min(mmin, sum[i - m]);
        if (sum[i] - mmin >= 0) {
          tag = true;
          break;
        }
      }
    }
    if (tag) {
      tl = mid + 1;
    } else {
      tr = mid;
    }
  }
  ll now = tl, mmin = 0;
  tag = false;
  for (int i = 1; i <= n; i++) {
    sum[i] = sum[i - 1] + arr[i] - now;
    if (i >= m) {
      mmin = min(mmin, sum[i - m]);
      if (sum[i] - mmin >= 0) {
        tag = true;
      }
    }
  }
  cout << (tag ? tl : now - 1) << '\n';
  return 0;
}