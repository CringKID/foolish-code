#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const ll kMaxN = 4e5 + 5;

struct interval {
  ll left, right, identity, ans;
} inter[kMaxN];
struct node {
  ll left, right, identity, opt;
  node(ll left_, ll right_, ll identity_, ll opt_) : left(left_), right(right_), identity(identity_), opt(opt_) {}
};
vector<node> que[kMaxN];
vector<ll> v;
ll n, m, k, len, arr[kMaxN], bucket[kMaxN], pos[kMaxN], block[kMaxN], ans[kMaxN];

bool compare(const interval& inter1, const interval& inter2) {
  if (block[inter1.left] ^ block[inter2.left]) {
    return block[inter1.left] < block[inter2.left];
  }
  return inter1.right < inter2.right;
}
ll counter(ll cur) {
  ll ans = 0;
  while (cur) {
    if (cur & 1) {
      ans++;
    }
    cur >>= 1;
  }
  return ans;
}

int main() {
  ios ::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);

  cin >> n >> m >> k;
  if (k > 14) {
    for (ll i = 1; i <= m; i++) {
      cout << 0 << '\n';
    }
    return 0;
  }
  len = sqrt(n);
  for (ll i = 0; i < 16384; i++) {
    if (counter(i) == k) {
      v.push_back(i);
    }
  }
  for (ll i = 1; i <= n; i++) {
    cin >> arr[i];
    block[i] = (i - 1) / len + 1;
  }
  for (ll i = 1; i <= m; i++) {
    cin >> inter[i].left >> inter[i].right;
    inter[i].identity = i;
  }

  sort(inter + 1, inter + m + 1, compare);
  for (ll i = 1; i <= n; i++) {
    pos[i] = bucket[arr[i]];
    for (ll j = 0; j < v.size(); j++) {
      bucket[arr[i] ^ v[j]]++;
    }
  }

  memset(bucket, 0, sizeof(bucket));
  ll left_ = 1, right_ = 0;
  for (ll i = 1; i <= m; i++) {
    if (left_ > inter[i].left) {
      que[right_].emplace_back(inter[i].left, left_ - 1, i, 1);
    }
    while (left_ > inter[i].left) {
      inter[i].ans -= pos[--left_];
    }

    if (right_ < inter[i].right) {
      que[left_ - 1].emplace_back(right_ + 1, inter[i].right, i, -1);
    }
    while (right_ < inter[i].right) {
      inter[i].ans += pos[++right_];
    }

    if (left_ < inter[i].left) {
      que[right_].emplace_back(left_, inter[i].left - 1, i, -1);
    }
    while (left_ < inter[i].left) {
      inter[i].ans += pos[left_++];
    }

    if (right_ > inter[i].right) {
      que[left_ - 1].emplace_back(inter[i].right + 1, right_, i, 1);
    }
    while (right_ > inter[i].right) {
      inter[i].ans -= pos[right_--];
    }
  }

  for (ll i = 1; i <= n; i++) {
    for (ll j = 0; j < v.size(); j++) {
      bucket[arr[i] ^ v[j]]++;
    }
    for (ll j = 0; j < que[i].size(); j++) {
      node temp = que[i][j];
      for (ll t = temp.left; t <= temp.right; t++) {
        if (t <= i && k == 0) {
          inter[temp.identity].ans += temp.opt * (bucket[arr[t]] - 1);
        } else {
          inter[temp.identity].ans += temp.opt * bucket[arr[t]];
        }
      }
    }
  }

  for (ll i = 1; i <= m; i++) {
    inter[i].ans += inter[i - 1].ans;
  }
  for (ll i = 1; i <= m; i++) {
    ans[inter[i].identity] = inter[i].ans;
  }
  for (ll i = 1; i <= m; i++) {
    cout << ans[i] << '\n';
  }
  return 0;
}