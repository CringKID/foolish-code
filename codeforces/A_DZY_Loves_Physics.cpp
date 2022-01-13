#include <iostream>
#include <algorithm>
#include <iomanip>

using namespace std;
using ll = long long;
const int kMaxN = 555;

int n, m, arr[kMaxN];
double mmax;
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  while (cin >> n >> m) {
    fill (arr, arr + n + 1, 0), mmax = 0;
    for (int i = 1; i <= n; i++) {
      cin >> arr[i];
    }
    for (int i = 0, from, to, val; i < m; i++) {
      cin >> from >> to >> val;
      mmax = max (mmax, (arr[from] + arr[to]) / (double) val);
    }
    cout << fixed << setprecision (15) << mmax << '\n';
  }
  return 0;
}