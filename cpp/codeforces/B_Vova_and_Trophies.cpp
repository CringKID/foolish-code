#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
using ll = long long;
const int kMaxN = 1e5 + 5;

char ch[kMaxN];
vector <int> ve;
int n, num, rec, tmp, ans, tag;
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n >> ch;
  for (int i = 0; i < n; i++) {
    ch[i] == 'G' ? num++ : 0;
    (ch[i - 1] == 'G' && ch[i] == 'S' && ch[i + 1] == 'G') ? ve.push_back (i) : void ();
  }
  for (int i = 0; i < n; i++) {
    ch[i] == 'G' ? tmp++ : (rec = max (rec, tmp), tmp = 0);
  }
  rec = min (max (rec, tmp) + 1, num);
  if (num == n) {
    cout << n << '\n';
    return 0;
  }
  if (num == 0) {
    cout << 0 << '\n';
    return 0;
  }
  if (int ans = 0, cnt = 0, tag = 0; !ve.size ()) {
    ans--;
    for (int i = 0; i < n; i++) {
      ch[i] == 'G' ? cnt++ : 0;
      ch[i] == 'S' ? (ans = max (ans, cnt), cnt = 0) : 0;
    }
    cout << min (num, max (ans, cnt) + 1) << '\n';
  } else {
    for (int to : ve) {
      for (int i = to - 1; i >= 0; i--) {
        if (ch[i] == 'S') {
          break;
        } else {
          cnt++;
        }
      }
      for (int i = to + 1; i < n; i++) {
        if (ch[i] == 'S') {
          break;
        } else {
          cnt++;
        }
      }
      ans = max (ans, cnt), cnt = 0;
    }
    cout << max (min (num, ans + 1), rec) << '\n';
  }
  return 0;
}