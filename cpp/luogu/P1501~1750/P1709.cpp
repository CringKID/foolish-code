#include <bits/stdc++.h>

using namespace std;

int n;
char ch[1919810 << 2];
int main() {
  ios ::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);

  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> ch[i];
  }

  for (int i = 0, j = 1, k = 0;;) {
    if (i >= n || j >= n) {
      cout << min(i, j) << '\n';
      return 0;
    }

    for (k = 0; ch[(i + k) % n] == ch[(j + k) % n] && k < n; k++)
      ;
    if (k == n) {
      cout << min(i, j) << '\n';
      return 0;
    }
    if (ch[(i + k) % n] > ch[(j + k) % n]) {
      i += k + 1;
    } else {
      j += k + 1;
    }
    if (i == j) {
      j++;
    }
  }
  return 0;
}