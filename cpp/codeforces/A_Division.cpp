#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;
using Pii = pair <int, int>;
using Pll = pair <ll, ll>;
const int kMaxN = 1e5 + 5, kMod = 1e9 + 7, kInf = 1e9;
const string str = "Division ";

int T, ratin;
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  for (cin >> T; T; T--) {
    cin >> ratin;
    cout << str << (ratin >= 1600 ? (ratin >= 1900 ? 1 : 2) : (ratin >= 1400 ? 3 : 4)) << '\n';
  }
  return 0;
}