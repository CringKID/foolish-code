#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;
const int kMaxN = 105;

int n;
ll arr1[kMaxN], arr2[kMaxN], val;
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> arr1[i];
    val += arr1[i];
  }
  val /= n;
  for (int i = 1; i <= n; i++) {
    arr1[i] -= val;
    arr2[i] = arr2[i - 1] + arr1[i];
  }
  sort (arr2 + 1, arr2 + n + 1), val = 0;
  for (int i = 1; i <= n; i++) {
    val += abs (arr2[n / 2 + 1] - arr2[i]);
  }
  cout << val << '\n';
  return 0;
}