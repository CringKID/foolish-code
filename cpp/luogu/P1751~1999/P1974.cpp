#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;
using ll = long long;
using Pii = pair <int, int>;
using Pll = pair <ll, ll>;
const int kMaxN = 1e4 + 5, kMod = 1e9 + 7, kInf = 1e9;

struct Number {
  int len, arr[3225];
  Number () {
    fill (arr, arr + len + 1, 0), len = 0;
  }
  void print () {
    for (int i = len - 1; i >= 0; i--) {
      cout << arr[i];
    }
    cout << '\n';
  }
  const Number operator + (const Number &another) const {
    int cur = 0;
    Number ans; ans.len = max (this -> len, another.len);
    for (int i = 0; i < ans.len; i++) {
      ans.arr[i] = this -> arr[i] + another.arr[i] + cur;
      cur = ans.arr[i] / 10, ans.arr[i] %= 10;
    }
    if (cur > 0) {
      ans.arr[++ans.len] = cur;
    }
    return ans;
  }
  const Number operator * (const Number &another) const {
    Number ans;
    for (int i = 0; i < this -> len; i++) {
      for (int j = 0; j < another.len; j++) {
        ans.arr[i + j] += this -> arr[i] * another.arr[j];
      }
    }
    ans.len = this -> len + another.len + 1;
    for (int i = 0; i < ans.len; i++) {
      ans.arr[i + 1] += ans.arr[i] / 10;
      ans.arr[i] = ans.arr[i] % 10;
    }
    for ( ; ans.arr[ans.len]; ans.len++) {
    }
    for ( ; !ans.arr[ans.len - 1]; ans.len--) {
    }
    return ans;
  }
} arr[kMaxN];
int n;
queue <int> que;
//#define contest
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);
#ifdef contest
  freopen (, , stdin);
  freopen (, , stdout);
#endif

  Pii ans;
  cin >> n;
  Number now; now.arr[now.len++] = 1;
  for (int i = 1; i <= n; i++) {
    que.push (i);
    arr[i] = now;
  }
  for ( ; que.size () != 1; que.push (ans.first)) {
    ans.first = que.front (); que.pop ();
    ans.second = que.front (); que.pop ();
    arr[ans.first] = arr[ans.first] * arr[ans.second];
    arr[ans.first] = arr[ans.first] + now;
  }
  arr[que.front ()].print ();
  return 0;
}