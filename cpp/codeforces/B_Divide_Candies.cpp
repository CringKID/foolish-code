#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;
const int kMaxN = 1e3 + 5;

ll cnt, sum;
int mat[kMaxN][kMaxN], n, m;
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= m; j++) {
      int cur = i * i + j * j;
      (cur % m == 0) ? (mat[i][j] = 1, cnt++) : 0;
    }
  }
  cnt *= ll (n / m) * (n / m);
  for (int i = 1; i <= n % m; i++) {
    for (int j = 1; j <= m; j++) {
      sum += mat[i][j] + mat[j][i];
    }
  }
  sum *= n / m;
  for (int i = 1; i <= n % m; i++) {
    for (int j = 1; j <= n % m; j++) {
      sum += mat[i][j];
    }
  }
  cout << cnt + sum << '\n';
  return 0;
}