#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
const int kMaxN = 155, kMaxR = 3e4 + 5;
struct Node {
  int sum, cur, tag;
} p[kMaxN];
int n, r, s, sum, dp[kMaxN][kMaxR];
vector <Node> ve;
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n >> r;
  for_each (p, p + n, [] (Node &P) {
    cin >> P.sum >> P.cur;
    P.cur >= 0 ? P.tag = 1 : (P.tag = 2, P.sum = max (P.sum, abs (P.cur))); 
  });
  sort (p, p + n, [] (Node p1, Node p2) {
    return (p1.tag == p2.tag) ? (p1.tag == 1 ? (p1.sum < p2.sum) : (p1.sum + p1.cur > p2.sum + p2.cur)) : (p1.tag < p2.tag);
  }), s = r;
  for (int i = 0; i < n; i++) {
    p[i].tag == 1 ? (s >= p[i].sum ? s += p[i].cur, sum++ : 0), void () : ve.push_back (p[i]);
  }
  dp[0][s] = sum;
  for (int i = 0; i < int (ve.size ()); i++) {
    for (int j = 0; j <= s; j++) {
      j >= ve[i].sum && j + ve[i].cur >= 0 ? (dp[i + 1][j + ve[i].cur] = max (dp[i + 1][j + ve[i].cur], dp[i][j] + 1)) : 0;
      dp[i + 1][j] = max(dp[i + 1][j], dp[i][j]);
    }
  }
  sum = 0;
  for (int i = 0; i <= s; i++) {
    sum = max (sum, dp[int (ve.size ())][i]);
  }
  cout << sum << '\n';
  return 0;
}