#include <bits/stdc++.h>

using namespace std;

using ll = long long;

template <typename F>
ll ternary_search(ll l, ll r, const F& f) {
  while (r - l > 2) {
    const ll ml = (l + r) / 2;
    const ll mr = ml + 1;
    if (f(ml) < f(mr)) {
      l = ml;
    } else {
      r = mr;
    }
  }

  return f(l + 1);
}

void solve() {
  int n, m;
  cin >> n >> m;
  ll res = numeric_limits<ll>::min();
  ll a = 0, b = 0;
  for (int i = 1; i <= n; i++) {
    ll x, y;
    cin >> x >> y;
    const auto f = [&](const ll k) {
      return a + b * k + k * (k + 1) / 2 * x;
    };

    if (x > 0) {
      res = max({res, f(1), f(y)});
    } else {
      res = max(res, ternary_search(0, y + 1, f));
    }
    a = f(y);
    b += x * y;
  }

  cout << res << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int test;
  cin >> test;
  for (int i = 0; i < test; ++i) solve();

  return 0;
}
