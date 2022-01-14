#include <algorithm>
#include <iostream>

using namespace std;
using ll = long long;
using Pii = pair<int, int>;
using Pll = pair<ll, ll>;
const int kMaxN = 1e6 + 5, kMod = 1e9 + 7, kInf = 1e9;

int n, m;
ll arr[kMaxN];
ll quickpow(ll base, ll index) {
  ll ans = 1;
  for (; index; index >>= 1, base = base * base % kMod) {
    if (index & 1) {
      ans = ans * base % kMod;
    }
  }
  return ans;
}
ll C(int x, int y) {
  ll cur = (arr[x - y] * arr[y]) % kMod;
  return arr[x] * quickpow(cur, kMod - 2) % kMod;
}
int main() {
  ios ::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);

  arr[0] = 1;
  for (int i = 1; i < kMaxN; i++) {
    arr[i] = arr[i - 1] * i % kMod;
  }
  cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    int cur;
    cin >> cur;
    n -= cur;
  }
  cout << C(n - 1, m - 1) << '\n';
  return 0;
}