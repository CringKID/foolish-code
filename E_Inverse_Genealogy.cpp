#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
const int kMaxN = 1e5 + 5;

int n, k, fath[kMaxN], tot;
bool full (int x) {
  return (x + 1 - ((x + 1) & -(x + 1))) == 0;
}
bool check (int n, int k) {
  int mmax = max ((n - 3) / 2, 0);
  if (k > mmax || n % 2 == 0 || n == 9 && k == 2) {
    return false;
  }
  if (full (n) && k == 1 || !full (n) && k == 0) {
    return false;
  }
  return true;
}
void build (int n, int k, int fa) {
  if (n == 3) {
    fath[tot + 1] = fa;
    fath[tot + 2] = tot + 1;
    fath[tot + 3] = tot + 1;
    tot += 3; return ;
  }
  fath[++tot] = fa, n--, fa = tot;
  for (int i = 1; i <= n / 2; i++) {
    for (int j = 0; j <= k; j++) {
      if (i * 2 > n - i && check (i, j) && check (n - i, k - j)) {
        return build (i, j, fa), build (n - i, k - j, fa);
      }
      if (i * 2 <= n - i && j < k && check (i, j) && check (n - i, k - 1 - j)) {
        return build (i, j, fa), build (n - i, k - 1 - j, fa);
      }
    }
  }
}
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n >> k;
  if (!check (n, k)) {
    cout << "NO" << '\n';
    return 0;
  }
  cout << "YES" << '\n';
  build (n, k, 0);
  for (int i = 1; i <= n; i++) {
    cout << fath[i] << ' ';
  }
  cout << '\n';
}