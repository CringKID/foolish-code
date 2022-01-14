#include <bits/stdc++.h>
using namespace std;
const int maxn = 105;
int q[maxn], top;
char c[maxn], b[maxn];
int main() {
  scanf("%s", c);
  static int len = strlen(c);
  for (register int i = 0; i < len; i++) {
    if (c[i] == '(') {
      q[++top] = i;
      b[i] = ')';
    }
    if (c[i] == '[') {
      q[++top] = i;
      b[i] = ']';
    }
    if (c[i] == ')' || c[i] == ']')
      if (!top || b[q[top]] != c[i])
        if (c[i] == ')')
          b[i] = '(';
        else
          b[i] = '[';
      else
        b[q[top--]] = ' ';
  }
  for (register int i = 0; i < len; i++) {
    if (b[i] == '(' || b[i] == '[') printf("%c", b[i]);
    printf("%c", c[i]);
    if (b[i] == ')' || b[i] == ']') printf("%c", b[i]);
  }
  return 0;
}