#include <iostream>
#include <algorithm>
#include <atcoder/all>

using namespace std;
using namespace atcoder;
using mint = modint998244353;
const int kMaxN = 1e6 + 5;

int n, q, cnt[kMaxN];
mint p[kMaxN], hsh[kMaxN], sum;
void calc (int x, int y) {  
  sum -= p[x] * cnt[x];
  (cnt[x] += y) %= 3;
  sum += p[x] * cnt[x];
}
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  p[0] = 1;
  for (int i = 1; i < kMaxN; i++) {
    p[i] = p[i - 1] * 131;
  }
  cin >> n >> q;
  for (int i = 1; i <= n; i++) {
    int x; cin >> x;
    for (int j = 2; j <= x / j; j++) {
      if (!(x % j)) {
        int cnt = 0;
        for ( ; !(x % j); x /= j, cnt++) {
        }
        calc (j, cnt);
      }
    }
    (x != 1 ? calc (x, 1) : void ());
    hsh[i] = sum;
  }
   for (int i = 1; i <= q; i++) {
    int l, r; cin >> l >> r;
    cout << (hsh[r] - hsh[l - 1] == 0 ? "Yes" : "No") << '\n';
  }
  return 0;
}