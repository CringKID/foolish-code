#include <iostream>
#include <algorithm>

using namespace std;
const int kMaxN = 1e5 + 5;

char str[kMaxN];
int sa[kMaxN], tmp[kMaxN], tmp2[kMaxN], cur[kMaxN], n, rank_[kMaxN], height[kMaxN];
void init (int m) {
  int *x = tmp, *y = tmp2;
  for (int i = 0; i < m; i++) {
    cur[i] = 0;
  }
  for (int i = 0; i < n; i++) {
    cur[x[i] = str[i]]++;
  }
  for (int i = 1; i < m; i++) {
    cur[i] += cur[i - 1];
  }
  for (int i = n - 1; i >= 0; i--) {
    sa[--cur[x[i]]] = i;
  }
  for (int k = 1; k <= n; k <<= 1) {
    int p = 0;
    for (int i = n - k; i < n; i++) {
      y[p++] = i;
    }
    for (int i = 0; i < n; i++) {
      if (sa[i] >= k) {
        y[p++] = sa[i] - k;
      }
    }
    for (int i = 0; i < m; i++) {
      cur[i] = 0;
    }
    for (int i = 0; i < n; i++) {
      cur[x[y[i]]]++;
    }
    for (int i = 1; i < m; i++) {
      cur[i] += cur[i - 1];
    }
    for (int i = n - 1; i >= 0; i--) {
      sa[--cur[x[y[i]]]] = y[i];
    }
    swap (x, y);
    p = 1, x[sa[0]] = 0;
    for (int i = 1; i < n; i++) {
      x[sa[i]] = (y[sa[i - 1]] == y[sa[i]] && y[sa[i - 1] + k] == y[sa[i] + k]) ? p - 1 : p++;
    }
    if (p >= n) {
      break;
    }
    m = p;
  }
}
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n >> str;
  init (128);
  for (int i = 0; i < n; i++) {
    rank_[sa[i]] = i;
  }
  int k = 0;
  for (int i = 0; i < n; i++) {
    if (!rank_[i]) {
      continue;
    }
    int j = sa[rank_[i] - 1];
    if (k) {
      k--;
    }
    while (str[i + k] == str[j + k]) {
      k++;
    }
    height[rank_[i]] = k;
  }
  long long ans = 0;
  for (int i = 0; i < n; i++) {
    ans += n - sa[i] - height[i];
  }
  cout << ans << '\n';
  return 0;
}