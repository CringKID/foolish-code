#include <bits/stdc++.h>

using namespace std;

const int kMaxN = 5e3 + 5;

struct Student {
  int id, val;
}stu[kMaxN];
bool compare (Student a, Student b) {
  return a.val > b.val;
}
int n, ans[kMaxN], now1 = 1, now2 = 2, now3 = 3, stable[kMaxN][kMaxN];

int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n;
  for (int i = 1; i <= n; i++){
    cin >> stu[i].val;
    stu[i].id = i;
  }
  sort (stu + 1, stu + n + 1, compare);
  stu[n + 1].val = 0;

  for (int i = 1; i <= n; i++) {
    stable[i][i] = i;
    int lim = stu[i].val - stu[i + 1].val;
    for (int j = i + 1; j <= n; j++) {
      int val = stu[j].val - stu[j + 1].val;
      if (val > lim) {
        lim = val;
        stable[i][j] = j;
      } else {
        stable[i][j] = stable[i][j - 1];
      }
    }
  }

  for (int i = 1; i <= n / 2; i++) {
    if (stu[i].val - stu[i + 1].val < stu[now1].val - stu[now1 + 1].val) continue;
    int tl = i + (i + 1) / 2, tr = min (i * 3, n - (i + 1) / 2);
    for (int j = tl; j <= tr; j++) {
      int kl = j + max ((i + 1) / 2, (j - i + 1) / 2), kr = min (j + min (i * 2, (j - i) * 2), n);
      if (kl > kr) continue;

      int k = stable[kl][kr];
      int val1 = stu[i].val - stu[i + 1].val, val2 = stu[j].val - stu[j + 1].val, val3 = stu[k].val - stu[k + 1].val;
      int ans1 = stu[now1].val - stu[now1 + 1].val, ans2 = stu[now2].val - stu[now2 + 1].val, ans3 = stu[now3].val - stu[now3 + 1].val;
      
      if (val1 > ans1 || (val1 == ans1 && (val2 > ans2 || (val2 == ans2 && val3 > ans3)))) {
        now1 = i, now2 = j, now3 = k;
      }
    }
  }

  for (int i = 1; i <= n; i++) {
    if (i <= now1) ans[stu[i].id] = 1;
    else if (i <= now2) ans[stu[i].id] = 2;
    else if (i <= now3) ans[stu[i].id] = 3;
    else ans[stu[i].id] = -1;
  }
  for (int i = 1; i <= n; i++){
    cout << ans[i] << ' ';
  }
  cout << '\n';
  return 0;
}