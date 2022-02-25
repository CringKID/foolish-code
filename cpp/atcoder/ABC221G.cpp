#include <iostream>
#include <algorithm>
#include <bitset>

using namespace std;
const int kMaxN = 2e3 + 5, kMaxM = 3.6e6 + 5;

bitset <kMaxM> dp[kMaxN];
int n, a, b, arr[kMaxN], rate, p1[kMaxN], p2[kMaxN];
bool judge (int k, int p[]) {
  if ((rate + k) & 1) {
    return false;
  }
  (k += rate) /= 2;
  if (k < 0 || k > rate || !dp[n][k]) {
    return false;
  }
  for (int i = n; i >= 1; i--) {
    if (!dp[i - 1][k]) {
      k -= arr[i];
      p[i] = 1;
    }
  }
  return true;
}

int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n >> a >> b;
  dp[0] = 1;
  for (int i = 1; i <= n; i++) {
    cin >> arr[i];
    rate += arr[i];
    dp[i] = dp[i - 1] | dp[i - 1] << arr[i];
  }
  if (judge (a + b, p1) && judge (a - b, p2)) {
    cout << "Yes" << '\n';
    for (int i = 1; i <= n; i++) {
      cout << ("LDUR"[p1[i] * 2 + p2[i]]);
    }
  } else {
    cout << "No" << '\n';
  }
  return 0;
}