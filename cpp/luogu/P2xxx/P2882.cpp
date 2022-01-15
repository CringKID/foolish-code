#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
using ll = long long;
using Pii = pair <int, int>;
using Pll = pair <ll, ll>;
const int kMaxN = 1e5 + 5, kMod = 1e9 + 7, kInf = 2e9;

int n, arr[kMaxN], sum[kMaxN], num[kMaxN], mmin = kInf, ans;
int check (int now) {
  memset (num, 0, sizeof (num));
  memcpy (sum, arr, sizeof (sum));
  int ans = 0;
  for (int i = 1; i <= n - now + 1; i++) {
    sum[i] ^= num[i] ^= num[i - 1];
    if (sum[i]) {
      ans++;
      num[i] ^= 1, num[i + now] ^= 1;
    }
  }
  for (int i = n - now + 2; i <= n; i++) {
    sum[i] ^= num[i] ^= num[i - 1];
    if (sum[i]) {
      return -1;
    }
  }
  return ans;
}
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n;
  for (int i = 1; i <= n; i++) {
    char ch;
    cin >> ch;
    arr[i] = (ch == 'B');
  }
  for (int i = 1; i <= n; i++) {
    int cur = check (i);
    if (~cur && cur < mmin) {
      mmin = cur;
      ans = i;
    }
  }
  cout << ans << ' ' << mmin << '\n';
  return 0;
}