#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;
using ll = long long;
using Pll = pair <ll, ll>;
const int kMaxN = 2e5 + 5, kInf = 2e9;

vector <Pll> ans;
map <ll, vector <ll> > Map;
ll n, k, dir[] = {-kInf - 1, -kInf + 1, -kInf, -1, 0, 1, kInf, kInf - 1, kInf + 1};
Pll node[kMaxN];
#define x first
#define y second
ll dist (ll n1, ll n2) {
  return (node[n1].x - node[n2].x) * (node[n1].x - node[n2].x) + (node[n1].y - node[n2].y) * (node[n1].y - node[n2].y);
}
ll encode (ll x, ll y) {
  return x / k * kInf + y / k;
}
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n >> k;
  for (ll i = 1; i <= n; i++) {
    cin >> node[i].x >> node[i].y;
  }
  for (ll i = 1; i <= n; i++) {
    Map[encode (node[i].x, node[i].y)].push_back (i);
  }
  for (ll i = 1; i <= n; i++) {
    for (ll di = 0; di < 9; di++) {
      for (ll j : Map[encode (node[i].x, node[i].y) + dir[di]]) {
        if (i < j && dist (i, j) <= k * k) {
          ans.emplace_back (i, j);
        }
      }
    }
  }
  sort (ans.begin (), ans.end ());
  cout << ans.size () << '\n';
  for (Pll P : ans) {
    cout << P.x << ' ' << P.y << '\n';
  }
  return 0;
}