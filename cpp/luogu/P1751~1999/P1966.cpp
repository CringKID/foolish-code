#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int kMaxN = 1e5 + 5, kMod = 1e8 - 3;

int n, tree[kMaxN << 1], que[kMaxN], num[kMaxN], identity[kMaxN], sum[kMaxN], id[kMaxN];
ll ans;

int Lowbit(int cur) {
  return cur & -cur;
}
void Update(int now) {
  while (now <= n) {
    tree[now] = (tree[now] + 1) % kMod;
    now += Lowbit(now);
  }
}
int Query(int cur) {
  int part = 0;
  while (cur) {
    part += tree[cur];
    if (part > kMod) {
      part -= kMod;
    }
    cur -= Lowbit(cur);
  }
  return part % kMod;
}

int main() {
  ios ::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);

  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> num[i];
    identity[i] = i;
  }
  for (int i = 1; i <= n; i++) {
    cin >> sum[i];
    id[i] = i;
  }
  sort(identity + 1, identity + n + 1, [](int x, int y) {
    return num[x] < num[y];
  });
  sort(id + 1, id + n + 1, [](int x, int y) {
    return sum[x] < sum[y];
  });

  for (int i = 1; i <= n; i++) {
    que[identity[i]] = id[i];
  }
  for (int i = n; i >= 1; i--) {
    Update(que[i]);
    ans = (ans + Query(que[i] - 1)) % kMod;
  }
  cout << ans % kMod << '\n';
  return 0;
}