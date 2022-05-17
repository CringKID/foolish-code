#include <iostream>
#include <algorithm>

using namespace std;
const int kMaxN = 255;

int arr[kMaxN][kMaxN], n, m, rol[kMaxN], col[kMaxN], target[kMaxN][kMaxN];
bool check (int x, int y) {
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      target[i][j] = (i * m + j >= x * m + y);
    }
  }
  rol[1] = target[1][1] ^ arr[1][1];
  for (int i = 1; i <= m; i++) {
    col[i] = target[1][i] ^ arr[1][i] ^ rol[1];
  }
  for (int i = 2; i <= n; i++) {
    rol[i] = target[i][1] ^ arr[i][1] ^ col[1];
    for (int j = 1; j <= m; j++) {
      if (target[i][j] != (arr[i][j] ^ rol[i] ^ col[j])) {
        return false;
      }
    }
  }
  return true;
}
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      cin >> arr[i][j];
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      bool tag = check (i, j);
      if (tag) {
        cout << "YES" << '\n';
        for (int i = 1; i <= n; i++) {
          cout << rol[i];
        }
        cout << '\n';
        for (int i = 1; i <= m; i++) {
          cout << col[i];
        }
        return 0;
      }
    }
  }
  cout << "NO" << '\n';
  return 0;
}