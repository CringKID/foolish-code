#include <iostream>
#include <algorithm>
#include <cstring>
#include <stack>

using namespace std;
using ll = long long;
using Pii = pair <int, int>;
using Pll = pair <ll, ll>;
const int kMaxN = 1e4 + 5, kMod = 1e9 + 7, kInf = 1e9;

Pii P[kMaxN];
stack <int> sta1, sta2;
int head[kMaxN], tot, arr[kMaxN], n, mmin[kMaxN], val[kMaxN], ans[kMaxN], t;
void add (int from, int to) {
  P[++tot] = {to, head[from]}, head[from] = tot;
}
bool DFS (int x) {
  if (val[x] == -1) {
    val[x] = 0;
  }
  for (int i = head[x]; i; i = P[i].second) {
    int to = P[i].first;
    if (val[to] == -1) {
      val[to] = val[x] ^ 1;
      if (!DFS (to)) {
        return false;
      }
    } else if (val[to] == val[x]) {
      return false;
    }
  }
  return true;
}
//#define contest
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);
#ifdef contest
  freopen (, , stdin);
  freopen (, , stdout);
#endif

  memset (val, -1, sizeof (val));
  cin >> n, mmin[n + 1] = 0x3f3f3f3f;
  for (int i = 1; i <= n; i++) {
    cin >> arr[i];
  }
  for (int i = n; i; i--) {
    mmin[i] = min (mmin[i + 1], arr[i]);
  }
  for (int i = 1; i < n; i++) {
    for (int j = i + 1; j <= n; j++) {
      if (arr[i] < arr[j] && arr[i] > mmin[j + 1]) {
        add (j, i), add (i, j);
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    if (val[i] == -1) {
      if (!DFS (i)) {
        cout << 0 << '\n';
        return 0;
      }
    }
  }
  for (int i = 1, now = 1; true; ) {
    if (now > n) {
      break;
    }
    if (!val[i] && (sta1.empty () || sta1.top () > arr[i])) {
      sta1.push (arr[i]), ans[++t] = 1, i++;
      continue;
    }
    if (!sta1.empty () && sta1.top () == now) {
      ans[++t] = 2, sta1.pop (), now++;
      continue;
    }
    if (val[i] == 1 && (sta2.empty () || sta2.top () > arr[i])) {
      sta2.push (arr[i]), ans[++t] = 3, i++;
      continue;
    }
    if (!sta2.empty () && sta2.top () == now) {
      sta2.pop (), ans[++t] = 4, now++;
      continue;
    }
  }
  for (int i = 1; i <= t; i++) {
    cout << char (ans[i] + 'a' - 1) << ' ';
  }
  return 0;
}