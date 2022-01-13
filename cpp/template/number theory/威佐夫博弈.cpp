#include <stdio.h>
int n, m;
int main() {
  scanf("%d %d", &n, &m);
  if (n < m) n ^= m ^= n ^= m;
  if (m == int(1.6180339887 * (n - m)))
    puts("0");
  else
    puts("1");
  return 0;
}