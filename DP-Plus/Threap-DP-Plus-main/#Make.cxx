#include <iostream>
#include "lib/mrrand.h"

using namespace std;

int main() {
  cout << rd(1e9) << ' ' << rd(1e9);
  return 0;
}