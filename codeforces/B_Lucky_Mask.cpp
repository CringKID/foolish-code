#include <bits/stdc++.h>

using namespace std;

int a, b;
int Judge (int now) {
  int rec = 0, mul = 1;
  while (now) {
    int tmp = now % 10; now /= 10;
    if (tmp == 4 || tmp == 7) {
      rec += mul * tmp;
      mul *=10;
    }
  }
  return rec;
}
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> a >> b;
  while (Judge (++a) != b) ;
  cout << a << '\n';
  return 0;
}