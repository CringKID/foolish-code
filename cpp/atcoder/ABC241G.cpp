#include <iostream>
#include <algorithm>
#include <atcoder/all>

using namespace std;
using namespace atcoder;
const int kN = 55;

vector <int> ve;
vector <vector <int> > tmp (kN, vector <int> (kN));
int n, m, cur, s, mat[kN][kN], arr[kN], t;
int solve (int k, vector <vector <int> > sum) {
  int tot = 0;
  for (int i = 0; i < n; i++) {
    !sum[k][i] ? sum[k][i]++, sum[i][k]-- : 0;
    sum[k][i] > 0 ? tot++ : 0;
  }
  if (!tot) {
    return false;
  }
  mf_graph <int> gra (cur);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < i; j++) {
      gra.add_edge (s, mat[i][j], 1);
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < i; j++) {
      sum[i][j] >= 0 ? gra.add_edge (mat[i][j], arr[i], 1) : 0;
      sum[i][j] <= 0 ? gra.add_edge (mat[i][j], arr[j], 1) : 0;
    }
  }
  for (int i = 0; i < n; i++) {
    i == k ? gra.add_edge (arr[i], t, tot) : gra.add_edge (arr[i], t, tot - 1);
  }
  int ans = gra.flow (s, t);
  return ans == n * (n - 1) / 2;
}
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n >> m;
  for (int i = 0, win, lose; i < m; i++) {
    cin >> win >> lose, win--, lose--;
    tmp[win][lose]++, tmp[lose][win]--;
  }
  s = cur++;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < i; j++) {
      mat[i][j] = cur++;
    }
  }
  for (int i = 0; i < n; i++) {
    arr[i] = cur++;
  }
  t = cur++;
  for (int i = 0; i < n; i++) {
    solve (i, tmp) ? ve.push_back (i + 1) : void ();
  }
  for (int i : ve) {
    cout << i << ' ';
  }
  return 0;
}