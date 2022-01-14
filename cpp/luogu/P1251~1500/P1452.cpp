#include <bits/stdc++.h>

using namespace std;
const int kMaxN = 1e6 + 5;

struct Node {
  long long x, y;
} node[kMaxN];
long long n, arr[kMaxN], bucket[kMaxN], tmp, mmax;

bool Judge(Node n1, Node n2, Node n3) {
  if (n1.x == n2.x) {
    return true;
  } else if (n1.y == n2.y) {
    return true;
  }
  return (n1.y - n2.y) * (n2.x - n3.x) > (n1.x - n2.x) * (n2.y - n3.y);
}
int main() {
  ios ::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);

  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> node[i].x >> node[i].y;
  }
  sort(node + 1, node + n + 1, [](Node n1, Node n2) {
    if (n1.x == n2.x) {
      return n1.y < n2.y;
    }
    return n1.x < n2.x;
  });
  tmp = 2, arr[1] = 2, arr[2] = 2;
  for (int i = 3; i <= n; i++) {
    while (tmp > 1 && Judge(node[arr[tmp - 1]], node[arr[tmp]], node[i])) {
      tmp--;
    }
    arr[++tmp] = i;
  }

  int temp = tmp;
  for (int i = 1; i <= tmp; i++) {
    bucket[arr[i]] = 1;
  }
  arr[++tmp] = n - 1;
  for (int i = n; i >= 1; i--) {
    if (bucket[i]) {
      continue;
    }
    while (tmp > temp && Judge(node[arr[tmp - 1]], node[arr[tmp]], node[i])) {
      tmp--;
    }
    arr[++tmp] = i;
  }

  for (int i = 1; i <= tmp; i++) {
    for (int j = i + 1; j <= tmp; j++) {
      mmax = max(mmax, (node[arr[i]].x - node[arr[j]].x) * (node[arr[i]].x - node[arr[j]].x) +
                           (node[arr[i]].y - node[arr[j]].y) * (node[arr[i]].y - node[arr[j]].y));
    }
  }
  cout << mmax << '\n';
  return 0;
}