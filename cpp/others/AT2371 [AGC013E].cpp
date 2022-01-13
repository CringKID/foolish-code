#include <bits/stdc++.h>

using namespace std;
using ll = long long;
const int kMod = 1e9 + 7;

struct Matrix {
  int mat[4][4];
  Matrix () {
    memset (mat, 0, sizeof (mat));
  }
  Matrix operator * (const Matrix another) {
    Matrix ans;
    for (int i = 1; i <= 3; i++) {
      for (int j = 1; j <= 3; j++) {
        for (int k = 1; k <= 3; k++) {
          ans.mat[i][j] = (ans.mat[i][j] + 1ll * mat[i][k] * another.mat[k][j]) % kMod;
        }
      }
    }
    return ans;
  }
} ans, m1, m2;
int n, m;
Matrix matquickpow (int index, Matrix base = m1) {
  Matrix ans;
  for (int i = 1; i <= 3; i++) {
    ans.mat[i][i] = 1;
  }
  while (index) {
    if (index & 1) {
      ans = ans * base;
    }
    base = base * base;
    index >>= 1;
  }
  return ans;
}

int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n >> m;
  m1.mat[1][1] = 1, m1.mat[1][2] = 2, m1.mat[1][3] = 1, m1.mat[2][2] = m1.mat[2][3] = 1, 
    m1.mat[3][1] = 1, m1.mat[3][2] = m1.mat[3][3] = 2, m2 = m1;
  m2.mat[3][1] = m2.mat[3][2] = 0, m2.mat[3][3] = 1, ans.mat[1][1] = 1;

  int cur, pre = -1;
  for (int i = 1; i <= m; i++, pre = cur) {
    cin >> cur;
    ans = ans * matquickpow (cur - pre - 1) * m2;
  }
  ans = ans * matquickpow (n - pre - 1);
  cout << ans.mat[1][3] << '\n';
  return 0;
}