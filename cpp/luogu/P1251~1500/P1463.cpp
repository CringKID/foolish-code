#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int n, Prime[25] = {0, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53};
ll Max = -1, Num = -1;

void Calculate(ll Arr, int Flag, int Temp, int Now) {
  if (Temp > Max || (Temp == Max && Arr < Num)) Num = Arr, Max = Temp;
  int j = 0, Res;
  ll i = Arr;
  while (j < Now) {
    j++;
    if (n / i < Prime[Flag]) break;
    Res = Temp * (j + 1), i = i * Prime[Flag];
    if (i <= n) Calculate(i, Flag + 1, Res, j);
  }
}

int main() {
  scanf("%d", &n), Calculate(1, 1, 1, 30), printf("%lld\n", Num);
  return 0;
}