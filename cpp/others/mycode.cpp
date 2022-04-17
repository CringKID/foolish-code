#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <deque>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <vector>
#define x first
#define y second
#define debug(x) cout << #x << ":" << x << endl;
using namespace std;
typedef long double ld;
typedef long long LL;
typedef pair<int, int> PII;
typedef pair<double, double> PDD;
typedef unsigned long long ULL;
const int N = 1e5 + 10, M = 2 * N, INF = 0x3f3f3f3f, mod = 998244353;
const double eps = 1e-8, pi = acos(-1), inf = 1e20;
#define tpyeinput int
inline char nc() {
  static char buf[1000000], *p1 = buf, *p2 = buf;
  return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1000000, stdin), p1 == p2) ? EOF : *p1++;
}
inline void read(tpyeinput &sum) {
  char ch = nc();
  sum = 0;
  while (!(ch >= '0' && ch <= '9')) ch = nc();
  while (ch >= '0' && ch <= '9') sum = (sum << 3) + (sum << 1) + (ch - 48), ch = nc();
}
int dx[] = {-1, 0, 1, 0}, dy[] = {0, 1, 0, -1};
int h[N], e[M], ne[M], w[M], idx;
void add(int a, int b, int v = 0) {
  e[idx] = b, w[idx] = v, ne[idx] = h[a], h[a] = idx++;
}
int n, m, k;
int a[N];
LL fc[N][(1 << 10) + 1], fs[N][(1 << 10) + 1];
// fc[i][j]：前i个数字且状态为j的方案数
// fs[i][j]：前i个数字且状态为j的数的和
// 数位dp -> 分类讨论  对于每一位  保证算贡献的数都在范围内, 重点在于对状态的贡献
// xxxxaxxxx  分3类
// 1. xxxxx非零且小于原数  则第i位 可以任意取  [0,9]
// 2. xxxx为零            则第i位 可以取 [1,9]
// 3. xxxx 为原数字       则第i位 可以取得[0, a - 1]
// 最后单独算一下原数是否符合即可
// 转移由前面转移过来
// 变成连续问题  直接连续来取
int main() {
  ios::sync_with_stdio(false), cin.tie(0);
  string str;
  cin >> str;
  int n = str.size();
  for (int i = 0; i < n; i++) a[i] = str[i] - '0';

  cin >> m;
  int mask = 0;
  for (int i = 0; i < m; i++) {
    int x;
    cin >> x;
    mask |= 1 << x;
  }

  int last = a[0], prebit = 1 << a[0];
  // 相当于前缀前缀且全为0的情况 因此只能由[1, a[i]) 转移过来
  for (int i = 1; i < a[0]; i++) {
    (fc[0][1 << i] += 1) % mod;
    (fs[0][1 << i] += i) % mod;
  }

  for (int i = 1; i < n; i++) {
    // 保证转移的时候这一位可以随便选取
    for (int j = 1; j < (1 << 10); j++)
      for (int x = 0; x < 10; x++) {
        fc[i][j | (1 << x)] = (fc[i][j | (1 << x)] + fc[i - 1][j] + mod) % mod;
        fs[i][j | (1 << x)] = (fs[i][j | (1 << x)] + fs[i - 1][j] * 10 + fc[i - 1][j] * x + mod) % mod;
      }

    for (int x = 1; x < 10; x++) {
      fc[i][1 << x] = (fc[i][1 << x] + 1 + mod) % mod;
      fs[i][1 << x] = (fs[i][1 << x] + x + mod) % mod;
    }

    // 不填满  前缀相同 如果这一位填到a[i] 那么f[i - 1][j]的这些已有的状态里就存在了abcd 就无法直接转移了，相当于一个分类讨论
    for (int x = 0; x < a[i]; x++) {
      fc[i][prebit | (1 << x)] = (fc[i][prebit | (1 << x)] + 1 + mod) % mod;
      fs[i][prebit | (1 << x)] = (fs[i][prebit | (1 << x)] + (LL)last * 10 + x + mod) % mod;
    }
    last = ((LL)last * 10 + a[i] + mod) % mod;
    prebit = prebit | (1 << a[i]);
  }
  // cout << last << endl;
  LL res = 0;
  for (int j = 0; j < (1 << 10); j++)
    if ((j & mask) == mask) res = (res + fs[n - 1][j]) % mod;

  if ((prebit & mask) == mask) res = (res + last) % mod;

  cout << res << endl;
  return 0;
} 