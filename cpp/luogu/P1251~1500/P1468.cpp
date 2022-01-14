#include <bits/stdc++.h>

using namespace std;

const int kMaxN = 105;

int n, c, arr1[kMaxN], arr2[kMaxN], top;
string str[kMaxN];
void admit() {
  string tmp = "";
  for (int i = 1; i <= n; i++) {
    tmp += char(arr2[i] + '0');
  }
  str[++top] = tmp;
}

int main() {
  ios ::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);

  cin >> n >> c;
  int sum;
  memset(arr1, -1, sizeof(arr1));
  while (cin >> sum && sum != -1) {
    arr1[sum] = 1;
  }
  while (cin >> sum && sum != -1) {
    arr1[sum] = 0;
  }

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      for (int q = 0; q < 2; q++) {
        for (int w = 0; w < 2; w++) {
          if (i + j + q + w > c) {
            continue;
          }
          if ((i + j) % 2 == (q + w) % 2 && c % 2 == 1) {
            continue;
          }
          if ((i + j) % 2 != (q + w) % 2 && c % 2 == 0) {
            continue;
          }

          for (int k = 1; k <= n; k++) {
            arr2[k] = 1;
          }
          if (i) {
            for (int k = 1; k <= n; k++) {
              arr2[k] ^= 1;
            }
          }
          if (j) {
            for (int k = 1; k <= n; k += 2) {
              arr2[k] ^= 1;
            }
          }
          if (q) {
            for (int k = 2; k <= n; k += 2) {
              arr2[k] ^= 1;
            }
          }
          if (w) {
            for (int k = 1; k <= n; k += 3) {
              arr2[k] ^= 1;
            }
          }

          int tag = 1;
          for (int k = 1; k <= n; k++) {
            if (arr1[k] == -1) {
              continue;
            }
            if (arr1[k] != arr2[k]) {
              tag = 0;
            }
          }
          if (tag) {
            admit();
          }
        }
      }
    }
  }

  sort(str + 1, str + top + 1);
  if (top == 0) {
    cout << "IMPOSSIBLE" << '\n';
  } else {
    for (int i = 1; i <= top; i++) {
      cout << str[i] << '\n';
    }
  }
  return 0;
}