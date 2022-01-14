#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int maxn = 15, maxm = 405, mod = 1e8;

int n, m, Cnt, Array[maxm], mmap[maxn];
ll dp[maxn][maxm];

void INIT(int Now, int Sum) {
  if (Now >= m) return Array[++Cnt] = Sum, void();
  INIT(Now + 1, Sum), INIT(Now + 2, Sum + (1 << Now));
}

int main() {
  scanf("%d %d", &n, &m), INIT(0, 0);
  for (int i = 1; i <= n; i++) {
    ll Counter = 0, Temp;
    for (int j = m; j >= 1; j--) scanf("%lld", &Temp), Counter += Temp * (1ll << (j - 1ll));
    mmap[i] = Counter;
  }

  for (int i = 1; i <= Cnt; i++)
    if ((mmap[1] & Array[i]) == Array[i]) dp[1][i] = 1;
  for (int i = 2; i <= n; i++)
    for (int j = 1; j <= Cnt; j++) {
      if ((mmap[i] & Array[j]) != Array[j]) continue;

      for (int k = 1; k <= Cnt; k++) {
        if ((mmap[i - 1] & Array[k]) != Array[k])
          continue;
        else if ((Array[k] & Array[j]) != 0)
          continue;

        dp[i][j] = (dp[i][j] + dp[i - 1][k]) % mod;
      }
    }

  ll Ans = 0;
  for (int i = 1; i <= Cnt; i++)
    if ((mmap[n] & Array[i]) == Array[i]) Ans = (Ans + dp[n][i]) % mod;
  return printf("%lld\n", Ans) & 0;
}