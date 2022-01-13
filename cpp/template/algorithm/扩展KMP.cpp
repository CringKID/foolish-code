#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e7 + 5;
int n, nxt[maxn], extend[maxn], lench, lennow;
char ch[maxn], now[maxn];
inline void calc() {
  nxt[0] = lennow;
  register int tmp = 0;
  while (now[tmp] == now[tmp + 1] && tmp + 1 < lennow) tmp++;
  nxt[1] = tmp;
  register int temp = 1;
  for (register int i = 2; i < lennow; i++)
    if (i + nxt[i - temp] < nxt[temp] + temp)
      nxt[i] = nxt[i - temp];
    else {
      register int tmp = max(nxt[temp] + temp - i, 0);
      while (now[tmp] == now[tmp + i] && tmp + i < lennow) tmp++;
      nxt[i] = tmp, temp = i;
    }
}
inline void zfunc() {
  calc();
  register int tmp = 0;
  while (ch[tmp] == now[tmp] && tmp < min(lench, lennow)) tmp++;
  extend[0] = tmp;
  register int temp = 0;
  for (register int i = 1; i < lench; i++)
    if (nxt[i - temp] + i < extend[temp] + temp)
      extend[i] = nxt[i - temp];
    else {
      register int tmp = max(extend[temp] + temp - i, 0);
      while (now[tmp] == ch[tmp + i] && tmp < lennow && tmp + i < lench) tmp++;
      extend[i] = tmp, temp = i;
    }
}
int main() {
  scanf("%s\n%s", ch, now), lench = strlen(ch), lennow = strlen(now);
  zfunc();
  register long long x = 0, y = 0;
  for (register int i = 0; i < lennow; i++) x ^= (long long)(i + 1) * (nxt[i] + 1);
  for (register int i = 0; i < lench; i++) y ^= (long long)(i + 1) * (extend[i] + 1);
  printf("%lld\n%lld\n", x, y);
  return 0;
}