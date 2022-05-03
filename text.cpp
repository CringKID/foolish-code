#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;
using Pii = pair <int, int>;
using Pll = pair <ll, ll>;
const int kMaxN = 1e5 + 5, kMod = 1e9 + 7, kInf = 1e9;

int n, arr[kMaxN];
void input (int &x) {
  cin >> x;
  x *= x;
}
//#define contest
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);
#ifdef contest
  freopen (, , stdin);
  freopen (, , stdout);
#endif

  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> arr[i];
    arr[i] *= arr[i];
  }
  for_each (arr + 1, arr + n + 1, input);
  
  return 0;
}