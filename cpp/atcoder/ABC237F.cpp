#include <iostream>
#include <algorithm>
#include <atcoder/modint>

using namespace std;
using namespace atcoder;
using mint = modint998244353;
using ll = long long;
using Pii = pair <int, int>;
using Pll = pair <ll, ll>;
const int kMaxN = 1e5 + 5, kMod = 1e9 + 7, kInf = 1e9;

int n, m;
mint dp[1005][15][15][15], rec;
//#define contest
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);
#ifdef contest
  freopen (, , stdin);
  freopen (, , stdout);
#endif

  cin >> n >> m;
  dp[0][m][m][m] = 1;
  for (int i = 0; i < n; i++) {
		for (int j = 0; j <= m; j++) {
			for (int k = 0; k <= m; k++) {
				for (int r = 0; r <= m; r++) {
					mint dx = dp[i][j][k][r];
					if (dx == 0) {
            continue;
          }
					for (int x = 0; x < m; x++) {
						if (x <= j) {
              dp[i + 1][x][k][r] += dx;
						} else if (x <= k) {
              dp[i + 1][j][x][r] += dx;
						} else if (x <= r) {
              dp[i + 1][j][k][x] += dx;
            }
					}
				}
			}
		}
	}
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < m; j++) {
      for (int k = 0; k < m; k++) {
        rec += dp[n][i][j][k];
      }
    }
  }
  cout << rec.val () << '\n';
  return 0;
}