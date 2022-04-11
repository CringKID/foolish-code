#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;
const int kMaxN = 1e6 + 5;

string str;
ll ans[kMaxN], rec;
int n, m, sa[kMaxN], x[kMaxN], y[kMaxN], val[kMaxN], rnk[kMaxN], height[kMaxN], stack[kMaxN], top;
void solvesa () {
  for (int i = 1; i <= n; i++) {
    val[x[i] = str[i]]++;
  }
  for (int i = 2; i <= m; i++) {
    val[i] += val[i - 1];
  }
  for (int i = n; i; i--) {
    sa[val[x[i]]--] = i;
  }
  for (int k = 1; k <= n; k <<= 1) {
    int num = 0;
    for (int i = n - k + 1; i <= n; ++i) {
      y[++num] = i;
    }
    for (int i = 1; i <= n; i++) {
      if (sa[i] > k) {
        y[++num] = sa[i] - k;
      }
    }
    for (int i = 1; i <= m; i++) {
      val[i] = 0;
    }
    for (int i = 1; i <= n; i++) {
      val[x[i]]++;
    }
    for (int i = 2; i <= m; i++) {
      val[i] += val[i - 1];
    }
    for (int i = n; i; i--) {
      sa[val[x[y[i]]]--] = y[i];
      y[i] = 0;
    }
    swap (x, y), x[sa[1]] = 1, num = 1;
    for (int i = 2; i <= n; i++) {
      x[sa[i]] = (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k]) ? num : ++num;
    }
    if (num == n) {
      break;
    }
    m = num;
  }
}
void solveheight () {
  for (int i = 1; i <= n; i++) {
    rnk[sa[i]] = i;
  }
  for (int i = 1, k = 0; i <= n; i++) {
    if (rnk[i] == 1) {
      continue;
    }
    if (k) {
      k--;
    }
    int j = sa[rnk[i] - 1];
    while (i + k <= n && j + k <= n && str[i + k] == str[j + k]) {
      k++;
    }
    height[rnk[i]] = k;
  }
}
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n >> str, m = 122, str = " " + str;
  solvesa (), solveheight (), stack[0] = 1;
  for (int i = 2; i <= n; i++) {
    while (top && height[stack[top]] >= height[i]) {
      rec -= 1ll * (stack[top] - stack[top - 1]) * height[stack[top]], top--;
    }
    rec += 1ll * (i - stack[top]) * height[i], stack[++top] = i, ans[sa[i]] += rec;
  }
  rec = top = 0, stack[0] = n + 1;
  for (int i = n; i >= 1; i--) {
    ans[sa[i]] += rec + n - sa[i] + 1;
    if (i == 1) {
      continue;
    }
    while (top && height[stack[top]] >= height[i]) {
      rec -= 1ll * (stack[top - 1] - stack[top]) * height[stack[top]], top--;
    }
    rec += 1ll * (stack[top] - i) * height[i], stack[++top] = i;
  }
  for (int i = 1; i <= n; i++) {
    cout << ans[i] << '\n';
  }
  return 0;
}