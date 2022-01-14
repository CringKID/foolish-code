#include <bits/stdc++.h>

using namespace std;

int n1, n2, n3, n4, t1, t2;
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n1 >> n2 >> n3 >> n4;
  if (n3 == n4 + 1) {
    t1 = t2 = n3;
    if (n1 >= t1 && n2 >= t2) {
      for (int i = 0; i <= n1 - t1; i++) {
        cout << 4;
      }
      for (int i = 0; i < n4; i++) {
        cout << 74;
      }
      for (int i = 0; i <= n2 - t2; i++) {
        cout << 7;
      }
      cout << '\n';
      return 0;
    }
  }
  if (n3 == n4) {
    t1 = n3 + 1, t2 = n4;
    if (n1 >= t1 && n2 >= t2) {
      for (int i = 0; i <= n1 - t1; i++) {
        cout << 4;
      }
      for (int i = 0; i < n4 - 1; i++) {
        cout << 74;
      }
      for (int i = 0; i <= n2 - t2; i++) {
        cout << 7;
      }
      cout << 4 << '\n';
      return 0;
    }
  }
  if (n3 == n4) {
    t1 = n3, t2 = n4 + 1;
    if (n1 >= t1 && n2 >= t2) {
      cout << 7;
      n4--, n2--, t2--;
      for (int i = 0; i <= n1 - t1; i++) {
        cout << 4;
      }
      for (int i = 0; i < n4; i++) {
        cout << 74;
      }
      for (int i = 0; i <= n2 - t2; i++) {
        cout << 7;
      }
      cout << '\n';
      return 0;
    } 
  }
  if (n4 == n3 + 1) {
    t1 = n3 + 1, t2 = n4;
    if (n1 >= t1 && n2 >= t2) {
      cout << 7;
      n4--, n2--, t2--;
      for (int i = 0; i <= n1 - t1; i++) {
        cout << 4;
      }
      for (int i = 0; i < n4 - 1; i++) {
        cout << 74;
      }
      for (int i = 0; i <= n2 - t2; i++) {
        cout << 7;
      }
      cout << 4 << '\n';
      return 0;
    }
  }
  cout << -1 << '\n';
  return 0;
}