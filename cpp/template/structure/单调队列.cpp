#include <bits/stdc++.h>

using namespace std;
const int kMaxN = 1e6 + 5;

int n, k, arr[kMaxN], tail;
deque<int> dq;
int main() {
  ios ::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);

  cin >> n >> k;
  for (int i = 0; i < n; i++) {
    cin >> arr[i];
  }

  for (int i = 0; i < n; i++) {
    while (!dq.empty() && dq.back() >= arr[i]) {
      dq.pop_back();
    }
    dq.push_back(arr[i]);
    if (i - tail >= k && arr[tail] == dq.front()) {
      tail++;
      dq.pop_front();
    } else if (i - tail >= k) {
      tail++;
    }
    if (i >= k - 1) {
      cout << dq.front() << ' ';
    }
  }
  cout << '\n';

  dq.clear();
  tail = 0;
  for (int i = 0; i < n; i++) {
    while (!dq.empty() && dq.back() <= arr[i]) {
      dq.pop_back();
    }
    dq.push_back(arr[i]);
    if (i - tail >= k && arr[tail] == dq.front()) {
      tail++;
      dq.pop_front();
    } else if (i - tail >= k) {
      tail++;
    }
    if (i >= k - 1) {
      cout << dq.front() << ' ';
    }
  }
  cout << '\n';
  return 0;
}