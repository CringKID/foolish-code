#include <bits/stdc++.h>
using namespace std;
const int maxn = 35;
int a[maxn], b[maxn], c[maxn], num[maxn], nxt[maxn], n, cnt;
char s1[maxn], s2[maxn], s3[maxn];
bool vis[maxn];
namespace Accept {
inline bool judge() {
  int t = 0;
  for (int i = n - 1; i >= 0; i--) {
    int x = num[a[i]], y = num[b[i]], z = num[c[i]];
    if ((x + y + t) % n != z) return false;
    t = (x + y + t) / n;
  }
  return true;
}
void dfs(int t) {
  if (num[a[0]] + num[b[0]] >= n) return;
  for (int i = n - 1; i >= 0; i--) {
    int x = num[a[i]], y = num[b[i]], z = num[c[i]];
    if (x != -1 && y != -1 && z != -1 && (x + y) % n != z && (x + y + 1) % n != z) return;
  }
  if (t == n) {
    if (judge()) {
      for (int i = 0; i < n; i++) printf("%d ", num[i]);
      exit(0);
    }
    return;
  }
  for (int i = n - 1; i >= 0; i--)
    if (!vis[i]) {
      num[nxt[t]] = i;
      vis[i] = true;
      dfs(t + 1);
      num[nxt[t]] = -1;
      vis[i] = false;
    }
  return;
}
}  // namespace Accept
int main() {
  scanf("%d", &n);
  scanf("%s%s%s", s1, s2, s3);
  for (int i = 0; i < n; i++) {
    a[i] = s1[i] - 'A';
    b[i] = s2[i] - 'A';
    c[i] = s3[i] - 'A';
    num[i] = -1;
  }
  for (int i = n - 1; i >= 0; i--) {
    if (!vis[a[i]]) {
      vis[a[i]] = true;
      nxt[cnt++] = a[i];
    }
    if (!vis[b[i]]) {
      vis[b[i]] = true;
      nxt[cnt++] = b[i];
    }
    if (!vis[c[i]]) {
      vis[c[i]] = true;
      nxt[cnt++] = c[i];
    }
  }
  for (int i = 0; i < n; i++) vis[i] = false;
  Accept::dfs(0);
  return 0;
}