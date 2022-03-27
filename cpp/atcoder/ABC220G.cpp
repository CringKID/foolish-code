#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <cmath>

using namespace std;
using ll = long long;
using node = pair <ll, ll>;
using segment = pair <node, node>;
const int kMaxN = 1e3 + 5;

ll n, arr[kMaxN], ans = -1;
vector <node> no (kMaxN);
map <segment, vector <node> > Map;
#define x first
#define y second
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> no[i].x >> no[i].y >> arr[i];
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (i != j) {
        node ni = no[i], nj = no[j];
        ll dx = ni.x - nj.x, dy = ni.y - nj.y, G = __gcd (abs (dx), abs (dy));  
        dx /= G, dy /= G;
        if (!dx) { dy /= abs (dy); }
        if (!dy) { dx /= abs (dx); }
        ll dx2 = -dy, dy2 = dx, s1 = ni.x + nj.x, s2 = dx * ni.y - dy * ni.x;
        if (dy) { s1 = (ni.y + nj.y) * dx2 - s1 * dy2; }
        if (!dx) { s2 = ni.x; }
        Map[segment (node (dx, dy), node (s1, dx2))].emplace_back (arr[i] + arr[j], s2);
      }
    }
  }
  for (pair <segment, vector <node> > P : Map) {
    if (P.second.size () > 1) {
      map <ll, ll> mp;
      for (node N : P.second) {
        mp[N.y] = max (mp[N.y], N.x);
      }
      vector <ll> ve;
      for (node N : mp) {
        ve.push_back (N.y);
      }
      if (ve.size () <= 1) {
        continue;
      }
      sort (ve.begin (), ve.end (), greater <ll> ());
      ans = max (ans, ve[0] + ve[1]);
    }
  }
  cout << ans << '\n';
  return 0;
}