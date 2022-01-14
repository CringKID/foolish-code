#include <iostream>
#include <algorithm>
#include <set>
#include <vector>

using namespace std;
using ll = long long;
const int kMod = 1e9 + 7;

int n, m;
ll seed, mmax;
struct Node {
  int left, right;
  mutable ll value;
  Node (int left_, int right_ = -1, ll value_ = 0) : left (left_), right (right_), value (value_) {
  }
  bool operator < (const Node & another) const {
    return left < another.left;
  }
} ;
set <Node> odt;
using iter = set <Node> :: iterator;

iter split (int cur) {
  iter itr = odt.lower_bound (Node (cur));
  if (itr != odt.end () && itr -> left == cur) {
    return itr;
  }

  itr--;
  int left = itr -> left, right = itr -> right;
  ll value = itr -> value;
  odt.erase (itr);
  odt.insert (Node (left, cur - 1, value));
  return odt.insert (Node (cur, right, value)).first;
}
void assign (int left, int right, ll value) {
  iter itright = split (right + 1), itleft = split (left);
  odt.erase (itleft, itright);
  odt.insert (Node (left, right, value));
}
void add (int left, int right, ll value) {
  iter itright = split (right + 1), itleft = split (left);
  for ( ; itleft != itright; itleft++) {
    itleft -> value += value;
  }
}

ll Rank (int left, int right, int cur) {
  vector <pair <ll, int> > ve;
  iter itright = split (right + 1), itleft = split (left);
  ve.clear ();
  for ( ; itleft != itright; itleft++) {
    ve.emplace_back (itleft -> value, itleft -> right - itleft -> left + 1);
  }
  sort (ve.begin (), ve.end ());

  for (auto itr = ve.begin (); itr != ve.end (); itr++) {
    cur -= itr -> second;
    if (cur <= 0) {
      return itr -> first;
    }
  }
  return -1;
}
ll quickpow (ll base, ll index, ll mod) {
  ll ans = 1, cur = base % mod;
  while (index) {
    if (index & 1) {
      ans = ans * cur % mod;
    }
    cur = cur * cur % mod;
    index >>= 1;
  }
  return ans;
}
ll query (int left, int right, int Left, int Right) {
  iter itright = split (right + 1), itleft = split (left);
  ll ans = 0;
  for ( ; itleft != itright; itleft++) {
    ans = (ans + 1ll * (itleft -> right - itleft -> left + 1) * quickpow (itleft -> value, 1ll * Left, 
      1ll * Right)) % Right;
  }
  return ans;
}
ll Rand () {
  ll cur = seed;
  seed = (seed * 7 + 13) % kMod;
  return cur;
}

int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n >> m >> seed >> mmax;
  for (int i = 1; i <= n; i++) {
    odt.insert (Node (i, i, Rand () % mmax + 1));
  }
  odt.insert (Node (n + 1, n + 1, 0));

  for (int i = 1; i <= m; i++) {
    int opt = int (Rand () % 4) + 1, left = int (Rand () % n) + 1, right = int (Rand () % n) + 1, x, y;
    if (left > right) {
      left ^= right ^= left ^= right;
    }
    if (opt == 3) {
      x = int (Rand () % (right - left + 1)) + 1;
      cout << Rank (left, right, x) << '\n';
    } else {
      x = int (Rand () % mmax) + 1;
    }
    if (opt == 1) {
      add (left, right, 1ll * x);
    } else if (opt == 2) {
      assign (left, right, 1ll * x);
    } else if (opt == 4) {
      y = int (Rand () % mmax) + 1;
      cout << query (left, right, x, y) << '\n';
    }
  }
  return 0;
}