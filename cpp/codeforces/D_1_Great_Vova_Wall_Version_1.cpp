#include <iostream>
#include <algorithm>

using namespace std;
string str;
int n;
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n, str = "";
  for (int i = 1, k; i <= n; i++) {
    cin >> k;
    str += k % 2 + '0';
  }
  for (int i = 0; i < n - 1; i++) {
    if (i >= 0 && str[i] == str[i + 1]) {
      str.erase (i, 2);
      i -= 2, n -= 2;
    }
  }
  cout << (n <= 1 ? "YES" : "NO") << '\n';
  return 0;
}