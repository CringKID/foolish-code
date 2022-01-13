#include <bits/stdc++.h>

using namespace std;
using ll = long long;
const int kMaxN = 1e5 + 5, kMod = 1e9 + 7;

int n, k, fac[kMaxN], inv[kMaxN], dp[kMaxN], tmp[kMaxN], lft;
map <int, int> mmap;
bool Judge (int now) {
  while (now) {
    if (now % 10 != 4 && now % 10 != 7) {
      return false;
    }
    now /= 10;
  }
  return true;
}
int DFS (int now) {
  return now == 1 ? 1 : (ll)(kMod - kMod / now) * DFS (kMod % now) % kMod;
}
int calc (int n, int m) {
  return (ll)fac[n] * inv[m] % kMod * inv[n - m] % kMod;
}

int main () {
  fac[0] = 1, inv[0] = 1;
  for (int i = 1; i <= kMaxN - 5; ++i) {
    fac[i] = (ll)fac[i - 1] * i % kMod;
    inv[i] = DFS (fac[i]);
  }
  scanf ("%d %d", &n, &k);
  for (int i = 0, cur; i < n; ++i) {
    scanf ("%d", &cur);
    if (Judge (cur)) {
      mmap[cur]++;
    } else {
      lft++;
    }
  }

  for (int i = 0; i <= k; i++) {
    dp[i] = calc (lft, i);
  }
  for (map <int, int> :: iterator itr = mmap.begin (); itr != mmap.end (); ++itr) {
    int cur = itr -> second;
    for (int i = k; i > 0; --i) {
      (dp[i] += 1ll * dp[i - 1] * cur % kMod) %= kMod;
    }
  }
  cout << dp[k] << '\n';
  return 0;
}