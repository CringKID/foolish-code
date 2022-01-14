#include <bits/stdc++.h>

using namespace std;

char record[15], check[15];
string sumx, sumy;

map<char, int> two, sumone;

int n;

int main() {
  cin >> n >> sumx;
  for (register int i = 1; i < n; i++) cin >> sumx, record[i] = sumx[0];

  for (register int i = 1; i < n; i++)
    for (register int j = 1; j <= n; j++) {
      cin >> sumx;
      if (j != 1 && j != 2 && sumx == sumy) return puts("ERROR!"), 0;

      sumy = sumx;
      if (sumx.size() == 2) two[record[i]]++, sumone[sumx[1]]++;
    }

  for (register int i = 1; i < n; i++)
    if (two[record[i]] != n - 2 - sumone[record[i]]) return puts("ERROR!"), 0;

  for (register int i = 1; i < n; i++) printf("%c=%d ", record[i], two[record[i]]);

  return printf("\n%d\n", n - 1) & 0;
}