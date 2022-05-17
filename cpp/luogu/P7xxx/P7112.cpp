#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;
using ll = long long;
const int kN = 605;

ll n, p, mat[kN][kN], ans = 1;
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n >> p;
  for (int i = 1; i <= n; i++) {
    for_each (mat[i] + 1, mat[i] + n + 1, [&] (ll &x) { cin >> x; });
  }
  for (int i = 1; i <= n; i++) {
    int rec = i, res = abs (mat[i][i]);
    for (int j = i + 1; j <= n; j++) {
      if (abs (mat[j][i]) > res) {
        rec = j, res = abs (mat[j][i]);
      }
    }
    if (rec != i) {
      for (int k = 1; k <= n; k++) {
        swap (mat[i][k], mat[rec][k]);
      }
      ans *= -1;
    }
    if (res < 1) {
      cout << 0 << '\n';
      return 0;
    }
    for (int j = i + 1; j <= n; j++) {
      if (abs (mat[j][i])) {
        for (int k = i + 1; k <= n; k++) {
          mat[j][k] = mat[j][k] * mat[i][i] % p - mat[i][k] * mat[j][i] % p;
        }
        mat[j][i] = 0;
      }
    }
    (ans *= mat[i][i]) %= p;
  }
  cout << (ans % p + p) % p << '\n';
  return 0;
}