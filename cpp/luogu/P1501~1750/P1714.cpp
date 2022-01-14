#include <bits/stdc++.h>
using namespace std;
const int maxn = 5e5 + 5;
int sum[maxn], n, m, x, ans = INT_MIN;
deque<int> q;
int main() {
  scanf("%d %d", &n, &m);
  for (register int i = 1; i <= n; i++) {
    scanf("%d", &x);
    sum[i] = sum[i - 1] + x;
  }
  q.push_front(0);
  for (register int i = 1; i <= n; i++) {
    while (!q.empty() && q.back() < i - m) q.pop_back();
    ans = max(ans, sum[i] - sum[q.back()]);
    while (!q.empty() && sum[i] <= sum[q.front()]) q.pop_front();
    q.push_front(i);
  }
  printf("%d\n", ans);
  return 0;
}