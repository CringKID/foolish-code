#include <bits/stdc++.h>

using namespace std;
const int kMaxN = 1e5 + 5;

pair <int, int> p[kMaxN];
int n, d, lft, rght, mid;
bool Judge (int mid) {
  deque <int> diq, deq;
  for (int i = 1; i <= n; i++) {
    for (; !diq.empty() && p[i].first - p[diq.front()].first > mid; diq.pop_front()) ;
    for (; !diq.empty() && p[i].second <= p[diq.back()].second; diq.pop_back()) ;
    for (; !deq.empty() && p[i].first - p[deq.front()].first > mid; deq.pop_front()) ;
    for (; !deq.empty() && p[i].first >= p[deq.back()].second; deq.pop_back()) ;
    diq.push_back(i), deq.push_back(i);
    if (p[deq.front()].second - p[diq.front()].second >= d) {
      return true;
    } 
  }
  return false;
}

int main () {
  freopen("fpot.in", "r", stdin);
  freopen("fpot.out", "w", stdout);

  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n >> d;
  for (int i = 1; i <= n; i++) {
    cin >> p[i].first >> p[i].second;
  }
  sort(p + 1, p + n + 1);

  rght = 1e6;
  while (lft <= rght) {
    mid = lft + rght >> 1;
    if (Judge (mid)) {
      rght = mid - 1;
    } else {
      lft = mid + 1;
    }
  }
  cout << (lft > 1e6 ? -1 : lft) << '\n';
  return 0;
}