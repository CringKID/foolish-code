#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5 + 5;

int n, len, p1[maxn], p2[maxn], mmap[maxn], dp[maxn];

int main() {
  scanf("%d", &n);
  for (register int i = 1; i <= n; i++) scanf("%d", &p1[i]), mmap[p1[i]] = i;
  for (register int i = 1; i <= n; i++) scanf("%d", &p2[i]), dp[i] = INT_MAX;

  dp[0] = 0;

  for (register int i = 1, l, r, mid; i <= n; i++) {
    r = len, l = 0;

    if (mmap[p2[i]] > dp[len])
      dp[++len] = mmap[p2[i]];
    else {
      while (l < r) {
        mid = (l + r) / 2;

        if (dp[mid] > mmap[p2[i]])
          r = mid;
        else
          l = mid + 1;
      }

      dp[l] = min(mmap[p2[i]], dp[l]);
    }
  }

  return printf("%d\n", len) & 0;
}