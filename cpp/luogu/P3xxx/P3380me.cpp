#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;
using Pii = pair <int, int>;
using Pll = pair <ll, ll>;
const int kMaxN = 4e6 + 5, kMod = 1e9 + 7, kInf = 2147483647;

int n, m, tot, ans, mmax, arr[kMaxN], size[kMaxN], cnt[kMaxN], ch[kMaxN][2], fath[kMaxN], status[kMaxN], root[kMaxN];
void ClearSplay (int x) {
  fath[x] = ch[x][0] = ch[x][1] = size[x] = cnt[x] = status[x] = 0;
}
void PushupSplay (int x) {
  size[x] = (ch[x][0] ? size[ch[x][0]] : 0) + (ch[x][1] ? size[ch[x][1]] : 0) + cnt[x];
}

void RotateSplay (int x) {
  int fa1 = fath[x], fa2 = fath[fa1];
  bool tag = (ch[fa1][1] == x);
  ch[fa1][tag] = ch[x][tag ^ 1];
  if (ch[x][tag ^ 1]) {
    fath[ch[x][tag ^ 1]] = fa1;
  }
  fath[x] = fa2;
  if (fa2) {
    ch[fa2][ch[fa2][1] == fa1] = x;
  }
  fath[fa1] = x;
  ch[x][tag ^ 1] = fa1;
  PushupSplay (fa1), PushupSplay (fa2);
}
void BalanceSplay (int now, int x, int top) {
  while (fath[x] != top) {
    int fa1 = fath[x], fa2 = fath[fa1];
    if (fa2 != top) {
      RotateSplay ((ch[fa2][0] == fa1) == (ch[fa1][0] == x) ? fa1 : x);
    }
    RotateSplay (x);
  }
  if (!top) {
    root[now] = x;
  }
}
void InsertSplay (int now, int value) {
  int x = root[now];
  if (!root[now]) {
    root[now] = x = ++tot;
    status[x] = value;
    size[x] = cnt[x] = 1;
    return fath[x] = ch[x][0] = ch[x][1] = 0, void ();
  }
  for (int pre = 0; true; ) {
    if (status[x] == value) {
      cnt[x]++;
      PushupSplay (pre);
      break;
    }
    pre = x, x = ch[x][value > status[x]];
    if (!x) {
      x = ++tot;
      status[x] = value;
      size[x] = cnt[x] = 1;
      ch[pre][value > status[pre]] = x;
      fath[x] = pre;
      ch[x][0] = ch[x][1] = 0;
      PushupSplay (pre);
      break;
    }
  }
  BalanceSplay (now, x, 0);
}
int FindrankSplay (int now, int value) {
  int x = root[now], rec = 0;
  while (x) {
    if (status[x] == value) {
      return rec + (ch[x][0] ? size[ch[x][0]] : 0);
    }
    if (status[x] < value) {
      rec += (ch[x][0] ? size[ch[x][0]] : 0) + cnt[x];
      x = ch[x][1];
    } else {
      x = ch[x][0];
    }
  }
  return rec;
}
int GetupSplay (int now, int value) {
  for (int x = root[now]; x; x = ch[x][value > status[x]]) {
    if (status[x] == value) {
      BalanceSplay (now, x, 0);
      return x;
    }
  }
  return 0;
}
int PreSplay (int now) {
  int x = ch[root[now]][0];
  while (ch[x][1]) {
    x = ch[x][1];
  }
  return x;
}
int PostSplay (int now) {
  int x = ch[root[now]][1];
  while (ch[x][0]) {
    x = ch[x][0];
  }
  return x;
}
void DeleteSplay (int now, int key) {
  int x = GetupSplay (now, key);
  if (cnt[x] > 1) {
    cnt[x]--;
    return PushupSplay (x);
  }
  if (!ch[x][0] && !ch[x][1]) {
    ClearSplay (root[now]);
    return root[now] = 0, void ();
  }
  if (!ch[x][0]) {
    int nxt = ch[x][0];
    root[now] = nxt;
    return fath[nxt] = 0, void ();
  }
  if (!ch[x][1]) {
    int nxt = ch[x][0];
    root[now] = nxt;
    return fath[nxt] = 0, void ();
  }
  int cur = PreSplay (now), save = root[now];
  BalanceSplay (now, cur, 0);
  ch[root[now]][1] = ch[save][1];
  fath[ch[save][1]] = root[now];
  ClearSplay (save);
  PushupSplay (root[now]);
}
int GetpreSplay (int now, int value) {
  for (int x = root[now]; x; ) {
    if (status[x] < value) {
      ans = max (ans, status[x]);
      x = ch[x][1];
    } else {
      x = ch[x][0];
    }
  }
  return ans;
}
int GetpostSplay (int now, int value) {
  for (int x = root[now]; x; ) {
    if (status[x] > value) {
      ans = min (ans, status[x]);
      x = ch[x][0];
    } else {
      x = ch[x][1];
    }
  }
  return ans;
}

void InsertSegtree (int rt, int l, int r, int now, int value) {
  InsertSplay (rt, value);
  if (l == r) {
    return ;
  }
  int mid = l + r >> 1;
  if (now <= mid) {
    InsertSegtree (rt << 1, l, mid, now, value);
  } else {
    InsertSegtree (rt << 1 | 1, mid + 1, r, now, value);
  }
}
void RankSegtree (int rt, int l, int r, int L, int R, int value) {
  if (l == L && r == R) {
    return ans += FindrankSplay (rt, value), void ();
  }
  int mid = l + r >> 1;
  if (R <= mid) {
    RankSegtree (rt << 1, l, mid, L, R, value);
  } else if (L > mid) {
    RankSegtree (rt << 1 | 1, mid + 1, r, L, R, value);
  } else {
    RankSegtree (rt << 1, l, mid, L, mid, value);
    RankSegtree (rt << 1 | 1, mid + 1, r, mid + 1, R, value);
  }
}
void UpdateSegtree (int rt, int l, int r, int now, int value) {
  DeleteSplay (rt, arr[now]), InsertSplay (rt, value);
  if (l == r) {
    return arr[now] = value, void ();
  }
  int mid = l + r >> 1;
  if (now <= mid) {
    UpdateSegtree (rt << 1, l, mid, now, value);
  } else {
    UpdateSegtree (rt << 1 | 1, mid + 1, r, now, value);
  }
}
void PreSegtree (int rt, int l, int r, int L, int R, int value) {
  if (l == L && r == R) {
    return ans = max (ans, GetpreSplay (rt, value)), void ();
  }
  int mid = l + r >> 1;
  if (R <= mid) {
    PreSegtree (rt << 1, l, mid, L, R, value);
  } else if (L > mid) {
    PreSegtree (rt << 1 | 1, mid + 1, r, L, R, value);
  } else {
    PreSegtree (rt << 1, l, mid, L, mid, value);
    PreSegtree (rt << 1 | 1, mid + 1, r, mid + 1, R, value);
  }
}
void PostSegtree (int rt, int l, int r, int L, int R, int value) {
  if (l == L && r == R) {
    return ans = min (ans, GetpostSplay (rt, value)), void ();
  }
  int mid = l + r >> 1;
  if (R <= mid) {
    PostSegtree (rt << 1, l, mid, L, R, value);
  } else if (L > mid) {
    PostSegtree (rt << 1 | 1, mid + 1, r, L, R, value);
  } else {
    PostSegtree (rt << 1, l, mid, L, mid, value);
    PostSegtree (rt << 1 | 1, mid + 1, r, mid + 1, R, value);
  }
}

int Getkth (int L, int R, int cur) {
  int l = 0, r = mmax + 1;
  while (l < r) {
    int mid = l + r >> 1;
    ans = 0, RankSegtree (1, 1, n, L, R, mid);
    if (ans < cur) {
      l = mid + 1;
    } else {
      r = mid;
    }
  }
  return l - 1;
}
//#define contest
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);
#ifdef contest
  freopen (, , stdin);
  freopen (, , stdout);
#endif

  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> arr[i];
    InsertSegtree (1, 1, n, i, arr[i]);
    mmax = max (mmax, arr[i]);
  }
  while (m--) {
    int opt, x, y, z;
    cin >> opt >> x >> y;
    if (opt == 1) {
      cin >> z;
      ans = 0;
      RankSegtree (1, 1, n, x, y, z);
      cout << ans + 1 << '\n';
    } else if (opt == 2) {
      cin >> z;
      cout << Getkth (x, y, z) << '\n';
    } else if (opt == 3) {
      UpdateSegtree (1, 1, n, x, y);
    } else if (opt == 4) {
      cin >> z;
      ans = -kInf;
      PreSegtree (1, 1, n, x, y, z);
      cout << ans << '\n';
    } else {
      cin >> z;
      ans = kInf;
      PostSegtree (1, 1, n, x, y, z);
      cout << ans << '\n';
    }
  }
  return 0;
}