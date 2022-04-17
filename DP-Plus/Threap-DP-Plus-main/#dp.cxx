#include <iostream>

using namespace std;

signed main() {
  int a, b;
  cin >> a >> b;
  cout << a + b + ((a + b) % 2 == 0);
  return 0;
}