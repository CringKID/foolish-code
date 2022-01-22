#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;
using Pii = pair <int, int>;
using Pll = pair <ll, ll>;
const int kMaxN = 1e7 + 5, kMod = 1e9 + 7, kInf = 1e9;

bool tag1[kMaxN], tag2[kMaxN];
int arr[kMaxN], n, m, cur, tot = 1;
//#define contest
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);
#ifdef contest
  freopen (, , stdin);
  freopen (, , stdout);
#endif

  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> cur;
    arr[tot++] = cur;
    for (int j = 1; j <= m; j++) {
      if (!tag2[cur - j] && cur - j >= 0) {
        arr[tot++] = cur - j;
        tag2[cur - j] = true;
      }
    }
  }
  tot--;
  int mmin = kInf;
  for (int i = 1; i <= n; i++) {
    mmin = min (mmin, arr[i]);
  }
  int sum = __gcd (arr[1], arr[2]);
  for (int i = 3; i <= n; i++) {
    sum = __gcd (sum, arr[i]);
  }
  if (sum > 1 || mmin == 1) {
    cout << -1 << '\n';
    return 0;
  }
  tag1[0] = false;
  int now = 0;
  for (int i = 0; i < mmin; now++) {
    if (tag1[now]) {
      for (int j = 1; j <= n; j++) {
        tag1[now + arr[i]] = true;
      }
      i++;
    } else {
      i = 0;
    }
  }
  cout << now - mmin - 1 << '\n';
  return 0;
}