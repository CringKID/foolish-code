#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int kMod = 998244353;

ll t, p, q, r, l;
struct node {
  ll cnt1, cnt2, cnt3, cnt4, tag1, tag2;
  node() {
    cnt1 = cnt2 = cnt3 = cnt4 = tag1 = tag2 = 0;
  }
  node operator+(node another) {
    node ans;
    ans.cnt1 = (cnt1 + another.cnt1) % kMod, ans.cnt2 = (cnt2 + another.cnt2) % kMod;
    ans.cnt3 = (cnt3 + another.cnt3 + cnt2 * another.cnt2) % kMod, ans.cnt4 = (cnt4 + another.cnt4 + cnt1 * another.cnt2) % kMod;
    ans.tag1 = (tag1 + another.tag1 + ((cnt1 * cnt1) % kMod) * another.cnt2 + (2 * cnt1 * another.cnt4) % kMod) % kMod;
    ans.tag2 = ((tag2 + another.tag2 + ((cnt1 * cnt2) % kMod) * another.cnt2) % kMod + cnt1 * another.cnt3 + cnt2 * another.cnt4) % kMod;
    return ans;
  }
} node1, node2, ans;
node quickpow(node a, ll k) {
  node Ans;
  while (k) {
    if (k & 1) Ans = Ans + a;
    a = a + a, k >>= 1;
  }
  return Ans;
}

ll Calc(ll a, ll b, ll c, ll d) {
  return ((long double)1.0 * a * b + c) / d;
}
node solve(ll p, ll q, ll r, ll l, node a, node b) {
  if (!l)
    return node();
  if (p >= q)
    return solve(p % q, q, r, l, a, quickpow(a, p / q) + b);
  ll temp = Calc(l, p, r, q);
  if (!temp)
    return quickpow(b, l);
  ll cnt = l - Calc(q, temp, -r - 1, p);
  return quickpow(b, (q - r - 1) / p) + a + solve(q, p, (q - r - 1) % p, temp - 1, b, a) + quickpow(b, cnt);
}

int main() {
  ios ::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);

  cin >> t;
  for (int i = 1; i <= t; i++) {
    cin >> l >> p >> r >> q;
    node1.cnt1 = 1, node1.cnt2 = 0, node1.cnt3 = 0, node1.cnt4 = 0, node1.tag1 = 0, node1.tag2 = 0;
    node2.cnt1 = 0, node2.cnt2 = 1, node2.cnt3 = 1, node2.cnt4 = 0, node2.tag1 = 0, node2.tag2 = 0;
    ans = quickpow(node1, r / q) + solve(p, q, r % q, l, node1, node2);
    cout << (ans.cnt4 + r / q) % kMod << ' ' << (ans.tag1 + ((r / q) % kMod) * ((r / q) % kMod)) % kMod << ' ' << ans.tag2 << '\n';
  }
  return 0;
}