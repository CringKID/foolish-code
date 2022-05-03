#include <iostream>
#include <algorithm>
#include <map>
using namespace std;
int n, m, t;
map <int, int> Map;
int main() {
  for (cin >> t; t; t--) {
    cin >> n, Map.clear ();
    for (int i = 1, x; i <= n; i++) {
      cin >> x, Map[x]++;
    }
    int maxVal = INT_MIN, maxKey;
    for (auto x : Map) {
      x.second > maxVal ? (maxVal = max (maxVal, x.second), maxKey = x.first) : 0;
    }
    cout << (maxVal >= 3 ? maxKey : -1) << '\n';
  }
  return 0;
}