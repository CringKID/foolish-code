#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

ll Quick_Pow(ll a, ll p, ll k) {
  if (p == 0) return 1 % k;
  ll Ans = 1;
  while (p > 0) {
    if (p & 1) Ans = Ans * a % k;
    a = a * a % k, p >>= 1;
  }

  return Ans % k;
}

ll Solve(ll a, ll b, ll p) {
  ll Sqrt = sqrt(p), Ans = 1;
  set<ll> Set;
  for (ll i = 0; i < Sqrt; i++) Set.insert(Ans), Ans = 1ll * Ans * a % p;

  Ans = Quick_Pow(Ans, p - 2, p);
  ll Temp = b;

  for (ll i = 0; i < p - 1; i += Sqrt) {
    if (Set.count(Temp)) {
      ll Val = Quick_Pow(a, i, p);
      while (Val != b) Val = Val * a % p, i++;
      return i;
    }
    Temp = Temp * Ans % p;
  }

  return -1;
}

int main() {
  ll b, n, p;
  scanf("%lld %lld %lld", &p, &b, &n);
  ll Ans = Solve(b, n, p);

  if (Ans == -1)
    return puts("no solution"), 0;
  else
    return printf("%lld\n", Ans) & 0;
}