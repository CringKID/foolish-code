#include <bits/stdc++.h>
using namespace std;
int n, x, y, z;
int main() {
  scanf("%d", &n);
  while (n--) {
    scanf("%d %d %d", &x, &y, &z);
    if (y == 9 && z == 30 || y == 1 && z == 30 || !((y + z) % 2))
      printf("YES\n");
    else
      printf("NO\n");
  }
  return 0;
}