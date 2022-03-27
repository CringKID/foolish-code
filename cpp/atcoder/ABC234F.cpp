#include <iostream>
#include <algorithm>
#include <stack>

using namespace std;
using ll = long long;
const int kMaxN = 3e5 + 5, kMod = 998244353;

int n;
ll arr[kMaxN], dp[kMaxN], maxans, minans;
stack <ll> max1, max2, min1, min2;
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> arr[i];
  }
  dp[0] = 1;
  for (int i = 1; i <= n; i++) {
    ll val = dp[i - 1];
    while (!max1.empty () && max1.top () < arr[i]) {
      maxans = (maxans - max1.top () * max2.top () % kMod + kMod) % kMod;
      val = (val + max2.top ()) % kMod;
      max1.pop (), max2.pop ();
    }
    maxans = (maxans + val * arr[i] % kMod) % kMod;
    max1.push (arr[i]), max2.push (val);
    val = dp[i - 1];
    while (!min1.empty () && min1.top () > arr[i]) {
      minans = (minans - min1.top () * min2.top () % kMod + kMod) % kMod;
      val = (val + min2.top ()) % kMod;
      min1.pop (), min2.pop ();
    }
    minans = (minans + val * arr[i] % kMod) % kMod;
    min1.push (arr[i]), min2.push (val);
    dp[i] = (maxans - minans + kMod) % kMod;
  }
  cout << dp[n] << '\n';
  return 0;
}