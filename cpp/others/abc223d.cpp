#include <bits/stdc++.h>

using namespace std;
const int kMaxN = 2e5 + 5;

int n, m, arr[kMaxN], degree[kMaxN];
vector <int> edge[kMaxN];
priority_queue <int, vector <int>, greater <int> > pq;
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n >> m;
  for (int i = 1, a, b; i <= m; i++) {
    cin >> a >> b;
    edge[a].push_back (b);
    degree[b]++;
  }
  for (int i = 1; i <= n; i++) {
    if (!degree[i]) {
      pq.push (i);
    }
  }
  int value = 0;
  while (!pq.empty ()) {
    int from = pq.top (); pq.pop ();
    arr[++value] = from;
    for (int now : edge[from]) {
      if (!(--degree[now])) {
        pq.push (now);
      }
    }
  }
  if (value != n) {
    cout << -1 << '\n';
    return 0;
  }
  for (int i = 1; i <= n; i++) {
    cout << arr[i] << ' ';
  }
  cout << '\n';
  return 0;
}