#include <iostream>
#include <algorithm>
#include <iomanip>

using namespace std;
using ll = long long;
using Pii = pair <int, int>;
using Pll = pair <ll, ll>;
const int kMaxN = 1e5 + 5, kMod = 1e9 + 7, kInf = 1e9;

int n, arr[kMaxN], dp2[kMaxN];
double dp1[kMaxN];
//#define contest
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);
#ifdef contest
  freopen (, , stdin);
  freopen (, , stdout);
#endif

  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> arr[i];
  }
  double l = 0, r = 1e9, mid;
  for (int i = 1; i <= 1000; i++) {
    fill (dp1, dp1 + n + 1, 0);
    mid = (l + r) / 2;
    dp1[0] = arr[0] - mid;
    for (int j = 1; j < n; j++) {
      if (j < 2) {
        dp1[j] = max (dp1[j], dp1[j - 1]) + arr[j] - mid;
      }
      if (j > 1) {
        dp1[j] = max (dp1[j - 1], dp1[j - 2]) + arr[j] - mid;
      }
    }
    if (max (dp1[n - 1], dp1[n - 2]) >= 0) {
      l = mid;
    } else {
      r = mid;
    }
  }
  cout << fixed << setprecision (10) << l << '\n';
  int l_ = 0, r_ = 1e9;
  while (l_ < r_) {
    int mid_ = (l_ + r_ + 1) / 2;
    fill (dp2, dp2 + n + 1, -1e9);
    dp2[0] = arr[0] - mid_;
    for (int i = 0; i < n; i++) {
      if (i < 2) {
        dp2[i] = 0;
      }
      if (i > 0) {
        dp2[i] = max (dp2[i], dp2[i - 1]);
      }
      if (i > 1) {
        dp2[i] = max (dp2[i], dp2[i - 2]);
      }
      dp2[i] += arr[i] >= mid_ ? 1 : -1;
    }
    if (max (dp2[n - 1], dp2[n - 2]) > 0) {
      l_ = mid_;
    } else {
      r_ = mid_ - 1;
    }
  }
  cout << l_ << '\n';
  return 0;
}