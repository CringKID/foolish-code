#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
using ll = long long;
using Pii = pair <int, int>;
using Pll = pair <ll, ll>;
const int kMaxN = 1e5 + 5, kMod = 1e9 + 7, kInf = 1e9;

int T;
vector <int> ve;
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  for (int i = 1; ve.size () < 1000; i++) {
    if (i % 3 && i % 10 != 3) {
      ve.push_back (i);
    }
  }
  cin >> T;
  while (T--) {
    int cur;
    cin >> cur;
    cout << ve[cur - 1] << '\n';
  }
  return 0;
}