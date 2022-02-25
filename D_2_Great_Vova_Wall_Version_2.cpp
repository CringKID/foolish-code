#include <iostream>
#include <algorithm>
#include <stack>
#include <queue>

using namespace std;
stack <int> sta;
queue <int> que;
int n, mmax, len;

int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n;
  for (int i = 1, k; i <= n; i++) {
    cin >> k, que.push (k);
    mmax = max (mmax, k);
  }
  while (!que.empty ()) {
    if (sta.empty ()) {
      sta.push (que.front ());
      que.pop (), len++;
      continue;
    }
    if (sta.top () == que.front ()) {
      sta.pop ();
      if (!sta.empty () && sta.top () < que.front ()) {
        sta.push (-1);
      }
      len--, que.pop ();
    } else {
      sta.push (que.front ());
      que.pop (), len++;
    }
  }
  cout << ((sta.size () == 0 || (sta.size () == 1 && mmax == sta.top ())) ? "YES" : "NO") << '\n';
  return 0;
}