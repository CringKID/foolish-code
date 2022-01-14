#include <bits/stdc++.h>

using namespace std;

const int maxn = 2e5 + 5;

int n, d[maxn], tl[maxn], tr[maxn];
double ans = 2e18, L[maxn], R[maxn], D[maxn], U[maxn];

struct node {
  double x, y;
} s[maxn];

inline double dist(int a, int b) { return (s[a].x - s[b].x) * (s[a].x - s[b].x) + (s[a].y - s[b].y) * (s[a].y - s[b].y); }

bool cmp1(node a, node b) { return a.x < b.x; }
bool cmp2(node a, node b) { return a.y < b.y; }

void update(int x) {
  L[x] = R[x] = s[x].x, D[x] = U[x] = s[x].y;

  if (tl[x]) L[x] = min(L[x], L[tl[x]]), R[x] = max(R[x], R[tl[x]]), D[x] = min(D[x], D[tl[x]]), U[x] = max(U[x], U[tl[x]]);
  if (tr[x]) L[x] = min(L[x], L[tr[x]]), R[x] = max(R[x], R[tr[x]]), D[x] = min(D[x], D[tr[x]]), U[x] = max(U[x], U[tr[x]]);
}

int build(int l, int r) {
  if (l >= r) return 0;

  register int mid = (l + r) >> 1;
  register double arrx = 0, arry = 0, arrx_ = 0, arry_ = 0;

  for (register int i = l; i <= r; i++) arrx += s[i].x, arry += s[i].y;
  arrx /= (double)(r - l + 1), arry /= (double)(r - l + 1);
  for (register int i = l; i <= r; i++) arrx_ += (s[i].x - arrx) * (s[i].x - arrx), arry_ += (s[i].y - arry) * (s[i].y - arry);

  if (arrx_ >= arry_)
    d[mid] = 1, nth_element(s + l, s + mid, s + r + 1, cmp1);
  else
    d[mid] = 2, nth_element(s + l, s + mid, s + r + 1, cmp2);

  tl[mid] = build(l, mid - 1), tr[mid] = build(mid + 1, r);
  update(mid);
  return mid;
}

inline double calc(int a, int b) {
  register int ans = 0;
  if (L[b] > s[a].x) ans += (L[b] - s[a].x) * (L[b] - s[a].x);
  if (R[b] < s[a].x) ans += (s[a].x - R[b]) * (s[a].x - R[b]);
  if (D[b] > s[a].y) ans += (D[b] - s[a].y) * (D[b] - s[a].y);
  if (U[b] < s[a].y) ans += (s[a].y - U[b]) * (s[a].y - U[b]);

  return ans;
}

void query(int l, int r, int x) {
  if (l > r) return;

  register int mid = (l + r) >> 1;
  if (mid != x) ans = min(ans, dist(x, mid));
  if (l == r) return;

  register double dis1 = calc(x, tl[mid]), dis2 = calc(x, tr[mid]);
  if (dis1 < ans && dis2 < ans) {
    if (dis1 < dis2) {
      query(l, mid - 1, x); /*if(dis2<ans) query(mid+1,r,x);*/
    } else {
      query(mid + 1, r, x); /*if(dis1<ans) query(l,mid-1,x);*/
    }
  } else {
    if (dis1 < ans) query(l, mid - 1, x);
    if (dis2 < ans) query(mid + 1, r, x);
  }
}

int main() {
  scanf("%d", &n);
  for (register int i = 1; i <= n; i++) scanf("%lf %lf", &s[i].x, &s[i].y);

  build(1, n);
  for (register int i = 1; i <= n; i++) query(1, n, i);

  return printf("%.4lf\n", sqrt(ans)) & 0;
}