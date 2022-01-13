#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;
using Pii = pair <int, int>;
using Pll = pair <ll, ll>;
const int kMaxN = 1e5 + 5, kMod = 1e9 + 7, kInf = 1e9;

int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  int T;
  cin >> T;
  while (T--) {
    string str;
    cin >> str;
    int record = 1e9;
    for (int i = 0; i < 64; i++) {
      string tmp = to_string (1ull << i);
      int cur = 0;
      for (int j = 0; j < int (str.length ()); j++) {
        if (cur < int (tmp.length ()) && str[j] == tmp[cur]) {
          cur++;
        }
      }
      record = min (record, int (str.length ()) + int (tmp.length ()) - cur * 2);
    }
    cout << record << '\n';
  }
  return 0;
}