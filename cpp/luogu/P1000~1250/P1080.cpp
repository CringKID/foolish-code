#include <bits/stdc++.h>
using namespace std;
const int maxn = 1010, maxm = 10010;
struct node {
  int lnum, rnum;
} people[maxn];
int lft[maxm], ans[maxm], tmp[maxm];
inline int read() {
  int X = 0;
  bool flag = 1;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    if (ch == '-') flag = 0;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    X = (X << 1) + (X << 3) + ch - '0';
    ch = getchar();
  }
  if (flag) return X;
  return ~(X - 1);
}
bool cmp1(node x, node y) {
  return x.lnum * x.rnum < y.lnum * y.rnum;
}
bool cmp2(int *x, int *y) {
  for (int i = maxm - 1; i >= 0; i--) {
    if (x[i] > y[i]) return true;
    if (x[i] < y[i]) return false;
  }
  return false;
}
void mul(int *x, int num) {
  for (int i = maxm - 2; i >= 0; i--) x[i] *= num;
  for (int i = 0; i < maxm - 1; i++) {
    x[i + 1] += (x[i] / 10);
    x[i] %= 10;
  }
}
void div(int *x, int *ans, int num) {
  memset(ans, 0, sizeof(ans));
  int t = 0;
  for (int i = maxm - 1; i >= 0; i--) {
    t = t * 10 + x[i];
    ans[i] = t / num;
    t %= num;
  }
}
int main() {
  int n = read();
  for (int i = 0; i <= n; i++) people[i].lnum = read(), people[i].rnum = read();
  sort(people + 1, people + n + 1, cmp1);
  lft[0] = 1;
  for (int i = 0; i <= n; i++) {
    div(lft, tmp, people[i].rnum);
    if (cmp2(tmp, ans))
      for (int i = 0; i < maxm; i++) ans[i] = tmp[i];
    mul(lft, people[i].lnum);
  }
  bool flag = 0;
  for (int i = maxm - 1; i >= 0; i--) {
    if (!flag) {
      if (ans[i])
        flag = 1;
      else
        continue;
    }
    printf("%d", ans[i]);
  }
  return 0;
}