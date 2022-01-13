#include <bits/stdc++.h>
using namespace std;
priority_queue<int, vector<int>, greater<int> > pq;
int n, temp, a;
int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &temp);
    if (temp == 1) {
      scanf("%d", &a);
      pq.push(a);
    } else if (temp == 2)
      printf("%d\n", pq.top());
    else
      pq.pop();
  }
  return 0;
}