#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>

using namespace std;
const int kMaxN = 2e5 + 5;

queue <int> que;
map <string, int> Map;
vector <int> edge[kMaxN];
int n, dp[kMaxN], ind[kMaxN], tot, arr[kMaxN];
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n;
  for (int i = 1, len; i <= n; i++) {
    string str; cin >> str;
    str = ' ' + str, len = str.size () - 1;
    string s1 = "", s2 = "";
    for (int j = 1; j <= 3; j++) {
      s1 += str[j];
    }
    for (int j = len - 2; j <= len; j++) {
      s2 += str[j];
    }
    !Map.count (s1) ? Map[s1] = ++tot : 0;
    !Map.count (s2) ? Map[s2] = ++tot : 0;
    arr[i] = Map[s2], ind[Map[s1]]++;
    edge[Map[s2]].push_back (Map[s1]);
  }
  for (int i = 1; i <= tot; i++) {
    !ind[i] ? dp[i] = 1, que.push (i) : void ();
  }
  while (!que.empty ()) {
    int from = que.front (); que.pop ();
    for (int to : edge[from]) {
      dp[to] == 0 ? ind[to]--, (dp[from] == 1 ? dp[to] = 2, que.push (to) : (!ind[to] ? dp[to] = 1, que.push (to) : void ())) : void ();
    }
  }
  for (int i = 1; i <= n; i++) {
    cout << (dp[arr[i]] == 1 ? "Takahashi" : (dp[arr[i]] == 2 ? "Aoki" : "Draw")) << '\n';
  }
  return 0;
}