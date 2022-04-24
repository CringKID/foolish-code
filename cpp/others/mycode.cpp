#include <iostream>
#include <map>
#include <queue>
#include <vector>
using namespace std;
const int MAX = 2e5 + 10;
struct node {
  int numA, numF;
  bool operator<(const node &n) const {
    if (this->numA == n.numA)
      return this->numF < n.numF;
    else
      return this->numA < n.numA;
  }
};
priority_queue<node, vector<node> > qu;
map<int, int> maps, map1;
int main() {
  int q;
  cin >> q;
  while (q--) {
    int n;
    cin >> n;
    int aa, f;

    for (int i = 0; i < n; i++) {
      cin >> aa >> f;
      maps[aa]++;
      map1[aa] += f;
    }

    map<int, int>::iterator it;
    for (it = maps.begin(); it != maps.end(); it++) {
      node now = {it->second, map1[it->first]};
      qu.push(now);
    }
    int flag = -1;
    int ans1 = 0, ans2 = 0;
    while (1) {
      if (qu.empty() || flag == 0) break;
      int sum = qu.top().numA;
      int cnt = qu.top().numF;
      qu.pop();
      if (flag != sum) {
        flag = sum;
        ans1 += sum;
        ans2 += cnt;
      } else {
        if (sum == cnt) {
          sum--;
          cnt--;
        } else
          sum--;
        qu.push({sum, cnt});
      }
    }
    while (!qu.empty()) qu.pop();
    maps.clear();
    map1.clear();
    cout << ans1 << " " << ans2 << endl;
  }
  return 0;
}