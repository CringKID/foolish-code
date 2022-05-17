#include <atcoder/all>
using namespace std;
int main() {
  int n, m, b, w;
  cin >> n >> m >> b >> w;
  using mint = atcoder::modint998244353;
  vector<mint> f(3000), fi = f;
  f[0] = fi[0] = 1;
  for (int i = 0; i < 2555; i++)
    f[i + 1] = f[i] * (i + 1), fi[i + 1] = fi[i] / (i + 1);
  auto c = [&](int n, int r) {
    return f[n] * (fi[r] * fi[n - r]);
  };
  mint d[55][55] = {};
  for (int x = 0; x <= n; x++)
    for (int y = 0; y <= m; y++) {
      if (x * y < b) continue;
      // d[x][y]=c(x*y,b);
      for (int i = 0; i <= x; i++)
        for (int j = 0; j <= y; j++) {
          // if(i==x&&j==y)continue;
          if (i * j < b) continue;
          if (x + y + i + j & 1)
            d[x][y] -= c(i * j, b) * c(x, i) * c(y, j);
          else
            d[x][y] += c(i * j, b) * c(x, i) * c(y, j);
        }
    }
  mint r = 0;
  for (int x = 0; x <= n; x++)
    for (int y = 0; y <= m; y++) {
      if ((n - x) * (m - y) < w) continue;
      r += c(n, x) * c(m, y) * d[x][y] * c((n - x) * (m - y), w);
    }
  cout << r.val() << endl;
}
