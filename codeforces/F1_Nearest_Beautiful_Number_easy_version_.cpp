#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;
using Pii = pair <int, int>;
using Pll = pair <ll, ll>;
const int kMaxN = 1e5 + 5, kMod = 1e9 + 7, kInf = 2e9;

int T, cur[15], n, k, record;
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cur[0] = 1;
  for (int i = 1; i <= 9; i++) {
    cur[i] = cur[i - 1] * 10;
  }
  cin >> T;
  while (T--) {
    cin >> n >> k, record = kInf;
    for (int number = 2; number < 1 << 10; number++) {
      if (__builtin_popcount (number) != k) {
        continue;
      }
      int big = __lg (number), lil = __builtin_ctz (number);
      ll rec = 0;
      for (int i = 9; i >= 0; i--) {
        int buc = n / cur[i] % 10;
        if ((number >> buc & 1) || (rec == 0 && buc == 0)) {
          if ((cur[i] - 1) / 9 * big >= n % cur[i]) {
            rec += 1ll * buc * cur[i];
            continue;
          }
        }
        buc++;
        while (~number >> buc & 1) {
          buc++;
        }
        rec += 1ll * buc * cur[i];
        rec += (cur[i] - 1) / 9 * lil;
        break;
      }
      record = min (1ll * record, rec);
    }
    cout << record << '\n';
  }
  return 0;
}