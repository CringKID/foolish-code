#include <iostream>
#include <algorithm>
#include <cstring>
#include <numeric>
#include <vector>

using namespace std;
const int kMaxN = 2e5 + 7;

struct Edge {
  int from, to;
} edge[kMaxN];
int fath[kMaxN], tag[kMaxN], n, m, d, k, u, v;
int root (int x) {
  return fath[x] == x ? x : (fath[x] = root (fath[x]));
};
int main () {
  while (cin >> n >> m >> k) {
    memset (tag, 0, sizeof (tag));
    for (int i = 1; i <= n; i++) {
      fath[i] = i;
    }
    for (int i = 1; i <= m; i++) {
      cin >> edge[i].from >> edge[i].to;
      if (edge[i].from != 1 && edge[i].to != 1) {
        int fx = root (edge[i].from), fy = root (edge[i].to);
        if (fx != root (fy)) {
          fath[fx] = fy;
        }
      }
    }
    int cnt = 0;
    for (int i = 1; i <= m; i++) {
      if (edge[i].from == 1 || edge[i].to == 1) {
        int fx = root (edge[i].from), fy = root (edge[i].to);
        if (fx != fy) {
          tag[i] = 2, fath[fx] = fy, cnt++;
        } else {
          tag[i] = 1;
        }
      }
    }
    if (cnt > k) {
      cout << "NO" << '\n';
      continue;
    }
    k -= cnt;
    for (int i = 1; i <= m; i++) {
      if (k == 0) {
        break;
      }
      if (tag[i] == 1) {
        tag[i] = 2, k--;
        int fx = root (edge[i].from), fy = root (edge[i].to);
        fath[fx] = fy;
      }
    }
    if (k != 0) {
      cout << "NO" << '\n';
      continue;
    }
    for (int i = 1; i <= n; i++) {
      fath[i] = i;
    }
    iota (fath + 1, fath + n + 1, 1);
    for (int i = 1; i <= m; i++) {
      if (tag[i] == 2) {
        int fx = root (edge[i].from), fy = root (edge[i].to);
        fath[fx] = fy;
      }
    }
    for (int i = 1; i <= m; i++) {
      if (edge[i].from != edge[i].to && edge[i].from != 1 && edge[i].to != 1) {
        int fx = root (edge[i].from), fy = root (edge[i].to);
        if (fx != fy) {
          fath[fx] = fy, tag[i] = 2;
        }
      }
    }
    cout << "YES" << '\n';
    for (int i = 1; i <= m; i++) {
      if (tag[i] == 2) {
        cout << edge[i].from << ' ' << edge[i].to << '\n';
      }
    }
  }
  return 0;
}