#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;
using Pii = pair <int, int>;
using Pll = pair <ll, ll>;
const int kMaxN = 35, kMod = 1e9 + 7, kInf = 1e9;

bool tag;
string str, del, part, cur;
int T, n, list[kMaxN], bucket[kMaxN], delen, m, arr[kMaxN];
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> T;
  while (T--) {
    cin >> str, n = str.length ();
    fill (list, list + kMaxN, -1);
    fill (bucket, bucket + kMaxN, 0);
    fill (arr, arr + kMaxN, 0);
    del.clear (), cur.clear ();

    for (int i = 0; i < n; i++) {
      list[str[i] - 'a'] = i;
      bucket[str[i] - 'a']++;
    }
    for (int i = 0; i < 26; i++) {
      if (list[i] != -1) {
        del += 'a' + i;
      }
    }
    sort (del.begin (), del.end (), [] (char ch1, char ch2) {
      return list[ch1 - 'a'] < list[ch2 - 'a'];
    }); //Delete inversions of letters

    delen = del.length (), m = 0;
    for (int i = 0; i < delen; i++) {
      arr[del[i] - 'a'] = i + 1;
    }
    tag = false;
    for (int i = 0; i < 26; i++) {
      if (arr[i]) {
        if (bucket[i] % arr[i]) {
          cout << -1 << '\n';
          tag = true;
          break;
        }
        m += bucket[i] / arr[i];
      }
    } //Keep track of how many times each letter appears and divide them in the order in which they are deleted.
    if (tag) {
      continue;
    }
    
    part = str.substr (0, m); // Take the first few letters of t to get s.
    for (int i = 1; i <= delen; i++) {
      for (int j = 0; j < m; j++) {
        if (arr[part[j] - 'a'] >= i) {
          cur += part[j];
        }
      }
    }
    if (cur != str) {
      cout << -1 << '\n';
      continue;
    } // Let's simulate it and see if it's the same as t.
    cout << part << ' ' << del << '\n';
  }
  return 0;
}