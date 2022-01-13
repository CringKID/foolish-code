#include <bits/stdc++.h>
using namespace std;
bool vis[100000005];
int Prime[100000005], cnt = 0, q, n;
void Euler_Prime() {
  for (long long i = 2; i <= n; ++i) {
    if (!vis[i]) Prime[++cnt] = i;
    for (long long j = 1; j <= cnt && Prime[j] * i <= n; ++j) {
      vis[Prime[j] * i] = 1;
      if (!i % Prime[j]) break;
    }
  }
}
int main() {
  scanf("%d %d", &n, &q);
  Euler_Prime();
  for (int i = 1; i <= q; i++) {
    int temp;
    scanf("%d", &temp);
    printf("%d\n", Prime[temp]);
  }
  return 0;
}