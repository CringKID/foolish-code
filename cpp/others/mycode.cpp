#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <ctime>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <string>
#include <vector>
// #define TIME

using namespace std;
using LL = long long;
using LD = double;
using Pll = pair<LL, LL>;
using Pdd = pair<LD, LD>;
using Vl = vector<LL>;
using Mll = map<LL, LL>;
using Vec = pair<Pdd, Pdd>;

const int kN = 1e5 + 1;

int q, o[kN], a[kN], b[kN], s[kN], d[kN];

void Add(int x, int v) {
  for (; x <= q; s[x] += v, x += x & -x) {
  }
}
int Query(int x) {
  int _s = 0;
  for (; x; _s += s[x], x -= x & -x) {
  }
  return _s;
}
int At(int r) {
  int x = 0, c = 0;
  for (int i = 17; ~i; --i) {
    x += 1 << i;
    if (x >= q || c + s[x] >= r) {
      x -= 1 << i;
    } else {
      c += s[x];
    }
  }
  return x + 1;
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> q;
  for (int i = 1; i <= q; ++i) {
    cin >> o[i] >> a[i];
    if (o[i] != 4) {
      b[i] = a[i];
    }
  }
  sort(b + 1, b + q + 1);
  int m = unique(b + 1, b + q + 1) - b;
  copy(b + 1, b + m, d + 1);
  for (int i = 1; i <= q; ++i) {
    if (o[i] != 4) {
      a[i] = lower_bound(b + 1, b + m, a[i]) - b;
    }
    if (o[i] == 1) {
      Add(a[i], 1);
    } else if (o[i] == 2) {
      Add(a[i], -1);
    } else if (o[i] == 3) {
      cout << Query(a[i] - 1) + 1 << endl;
    } else if (o[i] == 4) {
      cout << d[At(a[i])] << endl;
    } else if (o[i] == 5) {
      cout << d[At(Query(a[i] - 1))] << endl;
    } else {
      cout << d[At(Query(a[i]) + 1)] << endl;
    }
  }
#ifdef TIME
  fprintf(stderr, "\nTIME: %dms", clock());
#endif
  return 0;
}