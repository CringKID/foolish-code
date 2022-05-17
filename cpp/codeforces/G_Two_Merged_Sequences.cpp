#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
const int kMaxN = 2e5 + 5, kInf = 0x3f3f3f3f;

vector <int> ve1, ve2;
int n, arr[kMaxN], ans[kMaxN];
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> arr[i];
  }
  ve1.push_back (-1), ve2.push_back (kInf);
  for (int i = 0; i < n; i++) {
    int b1 = ve1.back (), b2 = ve2.back ();
    if (b1 < arr[i] && b2 <= arr[i]) {
      ve1.push_back (arr[i]);
    }
    if (b1 >= arr[i] && b2 > arr[i]) {
      ve2.push_back (arr[i]), ans[i] = 1;
    }
    if (b1 >= arr[i] && b2 <= arr[i]) {
      cout << "NO" << endl;
      return 0;
    }
    if (b1 < arr[i] && b2 > arr[i]) {
      if (i == n - 1) {
        ve1.push_back (arr[i]);
      } else {
        if (arr[i] < arr[i + 1]) {
          ve1.push_back (arr[i]);
        } else if (arr[i] > arr[i + 1]) {
          ve2.push_back (arr[i]), ans[i] = 1;
        } else {
          ve1.push_back (arr[i]);
        }
      }
    }
  }
  cout << "YES" << '\n';
  for (int i = 0; i < n; i++) {
    cout << ans[i] << ' ';
  }
  return 0;
}