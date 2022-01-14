#include <bits/stdc++.h>
using namespace std;
const int maxn = 45, maxm = 1005;
char ch[maxn];
int temp[maxm];
int n, k, lent;
struct node {
  int s[maxm], len;
} f[maxn][10];
void cal(int x, int y, int l, int r) {
  int t[maxn];
  int len = 0;
  for (int i = r; i >= l; i--) t[++len] = ch[i] - '0';
  lent = max(f[x][y].len, len);
  for (int i = 1; i <= f[x][y].len; i++)
    for (int j = 1; j <= len; j++) temp[i + j - 1] += f[x][y].s[i] * t[j];
  for (int i = 1; i <= lent; i++) {
    temp[i + 1] += temp[i] / 10;
    temp[i] %= 10;
  }
  while (temp[lent + 1] > 0) {
    lent++;
    temp[lent + 1] += temp[lent] / 10;
    temp[lent] %= 10;
  }
}
bool check(int x, int y) {
  if (lent != f[x][y].len) return lent > f[x][y].len;
  for (int i = lent; i >= 1; i--)
    if (f[x][y].s[i] != temp[i]) return f[x][y].s[i] < temp[i];
  return false;
}
int main() {
  scanf("%d %d", &n, &k);
  scanf("%s", ch + 1);
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= i; j++) f[i][0].s[j] = ch[i - j + 1] - '0';
    f[i][0].len = i;
  }
  for (int j = 1; j <= k; j++)
    for (int i = j + 1; i <= n; i++)
      for (int l = j; l < i; l++) {
        memset(temp, 0, sizeof(temp));
        cal(l, j - 1, l + 1, i);
        if (check(i, j)) {
          for (int p = 1; p <= lent; p++) f[i][j].s[p] = temp[p];
          f[i][j].len = lent;
        }
      }
  for (int i = f[n][k].len; i >= 1; i--) printf("%d", f[n][k].s[i]);
  return 0;
}