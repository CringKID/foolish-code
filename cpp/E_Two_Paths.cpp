#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
using ll = long long;
using Pii = pair <int, int>;
using Pll = pair <ll, ll>;
const int kMaxN = 2e4 + 5, kMod = 1e9 + 7, kInf = 1e9;

struct Edge {
  int from, to, dead;
} edge[kMaxN];

int n, m, deg[kMaxN], val[kMaxN], odds;
vector <int> ve[kMaxN], v1, v2;

void no_solution () {
  cout << -1 << '\n';
  exit (0);
}
void DFS (int i) {
  if (deg[i] & 1) {
    odds++;
  }
  val[i] = 1;
  for (int j = 0; j < ve[i].size (); j++) {
    if (!val[edge[ve[i][j]].to]) {
      DFS (edge[ve[i][j]].to);
    }
  }
}
void build(int i, vector<int> & ans, int cur = -1) {
  val[i] = 1;
  for (int j = 0; j < ve[i].size(); j++) {
    if (!edge[ve[i][j]].dead) {
      edge[ve[i][j]].dead = 1;
      edge[ve[i][j] ^ 1].dead = 1;
      build (edge[ve[i][j]].to, ans, ve[i][j] / 2 + 1);
    }
  }
  if (cur != -1) {
    ans.push_back (cur);
  }
}

void output (vector <int> & ans) {
  cout << ans.size() << '\n';
  for (int i = 0; i < ans.size(); i++)
    cout << ans[i] << '\n';
}

int main() {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  cin >> m, n = 10000;
  if (m < 2) {
    no_solution ();
  }
  for (int i = 0; i < m; i++) {
    int from, to;
    cin >> from >> to, from--, to--;
    deg[from]++, deg[to]++;
    edge[i << 1].from = from;
    edge[i << 1].to = to;
    edge[i << 1 | 1].from = to;
    edge[i << 1 | 1].to = from;
  }
  for (int i = 0; i < 2 * m; i++) {
    ve[edge[i].from].push_back(i);
  }

  vector <int> ac;
  for (int i = 0; i < n; i++) {
    if (deg[i] > 0 && !val[i]) {
      odds = 0, DFS (i);
      ac.push_back (odds);
    }
  }
  for (int i = 0; i < n; i++) {
    val[i] = 0;
  }
  if (ac.size () > 2) {
    no_solution ();
  }
  if (ac.size () == 2) {
    if (ac[0] > 2 || ac[1] > 2) {
      no_solution ();
    }
    int cur = (ac[0] == 2) + (ac[1] == 2);
    for (int i = 0; i < n; i++) {
      if (deg[i] > 0 && !val[i]) {
        if (!cur || deg[i] & 1) {
          if (cur) cur--;
          build (i, v1);
          break;
        }
      }
    }
    for (int i = 0; i < n; i++) {
      if (deg[i] > 0 && !val[i]) {
        if (!cur || deg[i] & 1) {
          if (cur) cur--;
          build (i, v2);
          break;
        }
      }
    }
  } else {
    if (ac[0] > 4) {
      no_solution ();
    }
    if (ac[0] <= 2) {
      int cur = (ac[0] == 2);
      for (int i = 0; i < n; i++) {
        if (deg[i] > 0 && !val[i]) {
          if (!cur || deg[i] & 1) {
            if (cur) cur--;
            build (i, v1);
            break;
          }
        }
      }
      v2.push_back (v1[v1.size () - 1]);
      v1.pop_back ();
    } else {
      int sum1 = -1, sum2 = -1;
      for (int i = 0; i < n; i++) {
        if (deg[i] & 1) {
          if (sum1 == -1) {
            sum1 = i;
          } else if (sum2 == -1) {
            sum2 = i;
          } else {
            break;
          }
        }
      }
      edge[m << 1].from = edge[m << 1 | 1].to = sum1;
      edge[m << 1].to = edge[m << 1 | 1].from = sum2;
      ve[edge[m << 1].from].push_back (m << 1);
      ve[edge[m << 1 | 1].from].push_back (m << 1 | 1);
      for (int i = 0; i < n; i++) {
        if (deg[i] & 1 && i != sum1 && i != sum2) {
          build (i, v1);
          break;
        }
      }
      int i; for (i = 0; i < v1.size (); i++) {
        if (v1[i] > m) {
          for (int j = i + 1; j < v1.size (); j++) {
            v2.push_back (v1[j]);
          }
          break;
        }
      }
      v1.erase (v1.begin () + i, v1.end ());
    }
  }
  output (v1), output (v2);
  return 0;
}
