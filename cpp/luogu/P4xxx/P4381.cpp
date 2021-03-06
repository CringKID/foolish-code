#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <list>

using namespace std;
using ll = long long;
using Pii = pair <int, int>;
using Pll = pair <ll, ll>;
const int kMaxN = 1e5 + 5, kMod = 1e9 + 7, kInf = 1e9;

struct Node {
  struct Edge {
    ll dist;
    Node *from, *to;
    Edge (Node *from_, Node *to_, ll dist_) {
      this -> from = from_, this -> to = to_;
      this -> dist = dist_;
    }
    Node* operator [] (Node *now) {
      return now == from ? to : from;
    }
  } ;
  ll height, rec, res;
  bool tag, top;
  std :: list <Edge*> list;
  Node () {
    tag = true, res = 0, height = 0, rec = 0, top = false;
  }
  void connect (Node *node, ll dist) {
    Edge *edge = new Edge (node, this, dist);
    this -> list.push_back (edge);
    node -> list.push_back (edge);
  }

  bool findcircle (Edge *edge, vector <Node*> &circle, vector <ll> &dist) {
    if (!tag) {
      circle.push_back (this);
      dist.push_back (edge -> dist);
      top = true;
      return true;
    }
    tag = false;
    Node* node;
    for (Edge* thisedge : list) {
      node = (*thisedge)[this];
      if (thisedge == edge) {
        continue;
      }
      if (node -> findcircle (thisedge, circle, dist)) {
        if ((*circle.begin ()) == this) {
          return false;
        }
        circle.push_back (this);
        dist.push_back (edge -> dist);
        top = true;
        return true;
      }
      if (!circle.empty ()) {
        return false;
      }
    }
    return false;
  }
  void InitAsATree (Edge* edge) {
    Node* node;
    tag = false;
    for (Edge* thisedge : list) {
      node = (*thisedge)[this];
      if (node -> top || thisedge == edge) {
        continue;
      }
      node -> InitAsATree (thisedge);
      if (height < thisedge -> dist + node -> height) {
        rec = height;
        height = thisedge -> dist + node -> height;
      } else {
        rec = max (rec, thisedge -> dist + node -> height);
      }
      res = max (res, node -> res);
    }
    res = max (height + rec, res);
  }
} **node;

using namespace std;
ll *arr, *dist;
ll solve (vector <Node*> &circle, vector <ll> &ndist) {
  ll n = circle.size (), res = 0;
  for (int i = 0; i < n; i++) {
    arr[i] = arr[i + n] = circle[i] -> height;
    dist[i] = dist[i + n] = ndist[i];
    res = max (res, circle[i] -> res);
  }
  for (int i = 1; i < (n << 1); i++) {
    dist[i] += dist[i - 1];
  }
  deque <int> dq;
  dq.push_back (0);
  for (int i = 1; i < (n << 1); i++) {
    while (!dq.empty () && i - dq.front () >= n) {
      dq.pop_front ();
    }
    res = max (res, arr[dq.front ()] + arr[i] + dist[i - 1] - dist[dq.front () - 1]);
    while (!dq.empty () && arr[i] - dist[i - 1] >= arr[dq.back ()] - dist[dq.back () - 1]) {
      dq.pop_back ();
    }
    dq.push_back (i);
  }
  return res;
}
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  int n;
  cin >> n;
  node = new Node*[n + 1];
  for (int i = 0; i <= n; i++) {
    node[i] = new Node ();
  }
  for (int i = 1; i <= n; i++) {
    int edge, dist;
    cin >> edge >> dist;
    node[i] -> connect (node[edge], dist);
  }
  arr = new ll[n << 1], dist = new ll[n << 1 | 1];
  *(dist++) = 0;
  ll ans = 0;
  for (int i = 1; i <= n; i++) {
    if (!node[i] -> tag) {
      continue;
    }
    vector <Node*> circle;
    vector <ll> dist;
    node[i] -> findcircle (NULL, circle, dist);
    for (Node* node : circle) {
      node -> InitAsATree (NULL);
    }
    ans += solve (circle, dist);
  }
  cout << ans << '\n';
  return 0;
}