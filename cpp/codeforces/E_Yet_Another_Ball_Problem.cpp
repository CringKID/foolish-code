#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
using Pii = pair <int, int>;
const int kMaxN = 1e5 + 5, kInf = 1e9;

int n, k;
vector <Pii> ve;
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n >> k;
  for (int i = 1; i <= k; i++) {
    for (int j = i + 1; j <= k && n > 0; n -= 2, j++) {
      ve.emplace_back (i, j);
      ve.emplace_back (j, i);
    }
  }
  if (n < 0) {
    ve.pop_back ();
  } else if (n > 0) {
    cout << "NO" << '\n';
    return 0;
  }
  cout << "YES" << '\n';
  for (Pii pa : ve) {
    cout << pa.first << ' ' << pa.second << '\n';
  }
  return 0;
}