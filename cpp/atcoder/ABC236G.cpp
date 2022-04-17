#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
using ll = long long;
using Pii = pair <int, int>;
using Pll = pair <ll, ll>;
using Vii = vector <vector <int> >;
const int kMaxN = 155, kInf = 1e9 + 7;

int n, t, l;
Vii make (int n, int m) {
  Vii ve (n, vector <int> (m, kInf));
  return ve;
}
Vii map = make (kMaxN, kMaxN), result = make (kMaxN, kMaxN);
Vii mul (Vii arr1, Vii arr2) {
  Vii ans = make (arr1.size (), arr2[0].size ());
  for (int i = 0; i < arr1.size (); i++) {
    for (int j = 0; j < arr2[0].size (); j++) {
      for (int k = 0; k < arr1[0].size (); k++) {
        ans[i][j] = min (ans[i][j], max (arr1[i][k], arr2[k][j]));
      }
    }
  }
  return ans;
}
//#define contest
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);
#ifdef contest
  freopen (, , stdin);
  freopen (, , stdout);
#endif

  cin >> n >> t >> l;
  for (int i = 1, from, to; i <= t; i++) {
    cin >> from >> to;
    map[from - 1][to - 1] = i;
  }
  for (int i = 0; i < n; i++) {
    result[i][i] = -kInf;
  }
  for ( ; l; map = mul (map, map), l >>= 1) {
    if (l & 1) {
      result = mul (result, map);
    }
  }
  for (int i = 0; i < n; i++) {
    if (result[0][i] == kInf) {
      result[0][i] = -1;
    }
    cout << result[0][i] << ' ';
  }
  return 0;
}