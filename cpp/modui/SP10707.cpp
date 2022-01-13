#include <bits/stdc++.h>

using namespace std;

const int kMaxN = 1e5 + 5;

int n, q, belong[kMaxN], block, arr[kMaxN], time_[kMaxN], depth[kMaxN], top[kMaxN], fath[kMaxN], 
  size_[kMaxN], son[kMaxN], start_[kMaxN], end_[kMaxN], opp[kMaxN], tot;
vector <int> v[kMaxN];
struct interval {
  int left, right, identity, lca, ans;
  bool operator < (const interval & another) const {
    return belong[left] == belong[another.left] ? right < another.right : belong[left] < belong[another.left];
  }
} inter[kMaxN];

void discret () {
  sort (time_ + 1, time_ + n + 1);
  int len = unique (time_ + 1, time_ + n + 1) - time_ - 1;
  for (int i = 1; i <= n; i++) {
    arr[i] = lower_bound (time_ + 1, time_ + len + 1, arr[i]) - time_;
  }
}

void DFS1 (int now, int father) {
  fath[now] = father;
  size_[now] = 1;
  start_[now] = ++tot;
  opp[tot] = now;
  for (int i = 0; i < v[now].size (); i++) {
    int to = v[now][i];
    if (depth[to]) continue;
    depth[to] = depth[now] + 1;
    DFS1 (to, now);
    size_[now] += size_[to];
    if (size_[to] > size_[son[now]]) son[now] = to;
  }
  end_[now] = ++tot;
  opp[tot] = now;
}
void DFS2 (int now, int cur) {
  top[now] = cur;
  if (!son[now]) return ;
  DFS2 (son[now], cur);
  for (int i = 0; i < v[now].size (); i++) {
    int to = v[now][i];
    if (top[to]) continue;
    DFS2 (to, to);
  }
}

int LCA (int x, int y) {
  while (top[x] != top[y]) {
    if (depth[top[x]] < depth[top[y]]) {
      swap (x, y);
    }
    x = fath[top[x]];
  }
  return depth[x] < depth[y] ? x : y;
}

int all, ans[kMaxN], visit[kMaxN], tag[kMaxN];
void add (int now) {
  if ((++tag[now]) == 1) {
    all++;
  }
}
void del (int now) {
  if ((--tag[now]) == 0) {
    all--;
  }
}
void modify (int now) {
  visit[now] ? del (arr[now]) : add (arr[now]);
  visit[now] ^= 1;
}

int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n >> q;
  block = sqrt (n);
  for (int i = 1; i <= n; i++) {
    cin >> arr[i];
    time_[i] = arr[i];
  }
  for (int i = 1; i <= n * 2; i++) {
    belong[i] = i / block + 1;
  }
  discret ();
  for (int i = 1; i <= n - 1; i++) {
    int x, y;
    cin >> x >> y;
    v[x].push_back (y);
    v[y].push_back (x);
  }
  depth[1] = 1;
  DFS1 (1, 0);
  DFS2 (1, 1);

  
  for (int i = 1; i <= q; i++) {
    int x, y;
    cin >> x >> y;
    if (start_[x] > start_[y]) {
      swap (x, y);
    }
    int lca = LCA (x, y);
    inter[i].identity = i;

    if (lca == x) {
      inter[i].left = start_[x];
      inter[i].right = start_[y];
    } else {
      inter[i].left = end_[x];
      inter[i].right = start_[y];
      inter[i].lca = lca;
    }
  }

  sort (inter + 1, inter + q + 1);
  int left_ = 1, right_ = 0, counter = 0;
  for (int i = 1; i <= q; i++) {
    while (left_ < inter[i].left) {
      modify (opp[left_++]);
      counter++;
    }
    while (left_ > inter[i].left) {
      modify (opp[--left_]);
      counter++;
    }
    while (right_ < inter[i].right) {
      modify (opp[++right_]);
      counter++;
    }
    while (right_ > inter[i].right) {
      modify (opp[right_--]);
      counter++;
    }

    if (inter[i].lca) {
      modify (inter[i].lca);
    }
    inter[i].ans = all;
    if (inter[i].lca) {
      modify (inter[i].lca);
    }
  }

  for (int i = 1; i <= q; i++) {
    ans[inter[i].identity] = inter[i].ans;
  }
  for (int i = 1; i <= q; i++) {
    cout << ans[i] << '\n';
  }
  
  return 0;
}