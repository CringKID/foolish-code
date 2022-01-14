#include <bits/stdc++.h>

using namespace std;

const int maxm = 1 << 9;

long long reg[maxm], res[maxm], dp[10][maxm][85], n, s, tot = 0;

int main() {
  scanf("%lld %lld", &n, &s), memset(dp, 0, sizeof(dp));

  for (register int i = 0; i < (1 << n); i++) {
    if (!(i & (i >> 1)) && !(i & (i << 1))) reg[i] = 1;

    register int val = i;
    while (val) {
      if (val % 2) res[i]++;
      val /= 2;
    }

    if (reg[i]) dp[1][i][res[i]] = 1;
  }

  for (register int i = 2; i <= n; i++)
    for (register int j = 0; j < (1 << n); j++)
      if (reg[j])
        for (register int k = 0; k < (1 << n); k++)
          if (reg[k] && !(j & k) && !(j & (k >> 1)) && !(j & (k << 1)))
            for (register int val = 0; val + res[k] <= s; val++) dp[i][k][val + res[k]] += dp[i - 1][j][val];

  for (register int i = 0; i < (1 << n); i++) tot += dp[n][i][s];

  return printf("%lld\n", tot) & 0;
}