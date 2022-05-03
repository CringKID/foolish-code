#include <iostream>
#include <algorithm>

using namespace std;

int n, T;
int main () {
  for (cin >> T; T; T--) {
    cin >> n;
    cout << (n % 3 == 1 ? "NO" : "YES") << '\n';
  }
  return 0;
}