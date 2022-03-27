#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;
const int kMaxN = 1e6 + 5, kMod = 998244353;

ll arr1[kMaxN], arr2[kMaxN], n, d, sum;
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n >> d;
  arr1[0] = arr1[1] = arr2[0] = 1, arr2[1] = 2;
  for (int i = 2; i <= n; i++) {
    arr1[i] = (arr1[i - 1] * 2) % kMod;
    arr2[i] = (arr2[i - 1] * 2) % kMod;
  }
  for (int i = 0; i <= min (d, n); i++) {
    int j = d - i;
    if (i < n && j < n) {
      int Max = max (i, j);
      (sum += ((arr2[n - Max] - 1) * ((arr1[i] * arr1[j]) % kMod) % kMod)) %= kMod;
    }
  }
  cout << sum * 2 % kMod << '\n';
  return 0;
}
