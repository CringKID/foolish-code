#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;
string str = "abc";

int n;
string s, t, cur;
vector <string> ve;
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n >> s >> t;
  do {
    for (int i = 1; i <= n; i++, cur += str) {
    }
    ve.push_back (cur), cur.clear ();
    ve.push_back (string (n, str[0]) + string (n, str[1]) + string (n, str[2]));
  } while (next_permutation (str.begin (), str.end ()));
  for (string res : ve) {
    if (res.find (s) == string :: npos && res.find (t) == string :: npos) {
      cout << "YES" << '\n' << res << '\n';
      return 0;
    }
  }
  cout << "NO" << '\n';
  return 0;
}