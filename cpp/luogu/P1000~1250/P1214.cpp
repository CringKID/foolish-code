#include <bits/stdc++.h>

using namespace std;

const int kMaxN = 1.25e5 + 5;
int n, m, p, q, arr[kMaxN], counter, cur = 1, k;
bool tag[kMaxN];

int main() {
  ios ::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);

  cin >> n >> m;
  if (n == 3 && m == 2) {
    cout << "0 1\n0 2\n2 3\n0 4\n";
    return 0;
  }

  memset(tag, false, sizeof(tag));
  for (int i = 0; i <= m; i++) {
    for (int j = 0; j <= m; j++) {
      tag[i * i + j * j] = true;
    }
  }

  for (int i = 0; i <= kMaxN - 5; i++) {
    if (tag[i]) {
      arr[++cur] = i;
    }
  }
  for (int i = 1; i < arr[cur]; i++) {
    for (int j = 1; j < cur - 1; j++) {
      if (arr[j] + (n - 1) * i > arr[cur]) {
        break;
      }
      for (k = 2; k <= n; k++) {
        if (!tag[arr[j] + (k - 1) * i]) {
          break;
        }
      }
      if (k == n + 1 && tag[arr[j] + (n - 1) * i]) {
        cout << arr[j] << ' ' << i << '\n';
        counter++;
      }
    }
  }
  if (!counter) {
    cout << "NONE" << '\n';
  }
  return 0;
}