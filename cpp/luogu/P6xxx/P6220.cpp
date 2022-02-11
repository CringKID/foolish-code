#include <iostream>
#include <vector>

using namespace std;

const int kMaxN = 505, kMaxM = kMaxN * kMaxN << 1;

int n, m, tag[kMaxM], val[kMaxM], t, sum, cur[kMaxM];
bool map[kMaxN][kMaxN], flag[kMaxM];
vector <int> ve[kMaxM];

int encode (int x, int y) {
  return (x - 1) * m + y;
}
bool DFS (int x) {
  if (val[x] ^ t) {
    val[x] = t;
    for (int i : ve[x]) {
      if (!tag[i] || DFS (tag[i])) {
        return tag[i] = x, tag[x] = i;
      }
    }
  }
  return 0;
}
void DFS2(int x) {
  if (flag[x]) {
    return ;
  }
  flag[x] = 1;
  for (int i : ve[x]) {
    if (tag[i] && !flag[i]) {
      flag[i] = 1;
      DFS2 (tag[i]);
    }
  }
}

int main() {
  ios :: sync_with_stdio (0);
  cin.tie (0), cout.tie (0);
  cin >> n >> m;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      char ch;
      cin >> ch;
      map[i][j] = (ch == '1');
    }
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m;) {
      for (int k = j++; j <= m && !map[i][j]; ++j) {
        cur[encode (i, j)] = encode (i, k);
      }
    }
  }
  for (int j = 1; j <= m; ++j) {
    for (int i = 1; i <= n;) {
      for (int k = i++; i <= n && !map[i][j]; ++i) {
        ve[cur[encode (i, j)]].push_back (encode (k + n, j));
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (map[i][j]) {
        t++;
        sum += DFS (encode (i, j));
      }
    }
  }
  cout << sum << '\n';
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (map[i][j] && !tag[encode (i, j)]) {
        DFS2 (encode (i, j));
      }
    }
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      if (map[i][j]) {
        if (!flag[encode (i, j)]) {
          cout << i << " " << j << " DESNO" << '\n';
        }
        if (flag[encode (i + n, j)]) {
          cout << i << " " << j << " DOLJE" << '\n';
        }
      }
    }
  }
  return 0;
}