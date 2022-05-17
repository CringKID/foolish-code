#include <iostream>
#include <algorithm>
#include <atcoder/all>

using namespace std;
using namespace atcoder;
using ll = long long;
using mint = modint998244353;
const int kMaxN = 1e6 + 5;

mint ans;
bool tag;
int T, n, m;
char str[kMaxN];
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  for (cin >> T; T; T--) {
    cin >> n >> str, m = n - 1 >> 1, ans = tag = 0;
    for (int i = 0; i <= m; i++) {
      ans = ans * 26 + str[i] - 'A';
    }
    for (int i = m; ~i; i--) {
      if (str[i] < str[n - i - 1]) {
        break;
      }
      if (str[i] > str[n - i - 1]) {
        tag = true;
        break;
      }
    }
    cout << (!tag ? ans + 1 : ans).val () << '\n';
  }
  return 0;
}