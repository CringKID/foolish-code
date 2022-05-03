#include <iostream>
#include <algorithm>
#include <atcoder/all>
#include <unordered_map>

using namespace std;
using mint = atcoder::modint1000000007;

mint inv;
int n, m;
unordered_map <int, mint> Map;
mint solve (int m) {
  if (Map.count (m)) {
    return Map[m];
  }
  mint rec = n;
  for (int l = 2, r; l <= n; l = r + 1) {
    if (!(m / l)) {
      break;
    }
    r = min (n, m / (m / l));
    rec += solve (m / l) * (r - l + 1);
  }
  return Map[m] = rec * inv;
}
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n >> m;
  Map[0] = 1, inv = mint (n - 1).inv ();
  cout << solve (m).val () << endl;
  return 0;
}