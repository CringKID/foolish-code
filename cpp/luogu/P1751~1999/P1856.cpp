#include <bits/stdc++.h>
#define y1 whyy1hasdefined
#define y2 whyy2hasdefined

using namespace std;
const int kMaxN = 8e5 + 5;

struct St {
  int x, y1, y2, flag;
} sto[kMaxN], orz[kMaxN];
int compare(St s1, St s2) {
  return s1.x == s2.x ? s1.flag > s2.flag : s1.x < s2.x;
}
int n, m, x1, y1, x2, y2, z, tot, arr1[kMaxN], arr2[kMaxN], base = 400000, ans;
int main() {
  ios ::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);

  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> x1 >> y1 >> x2 >> y2;
    sto[++tot] = St{x1, y1, y2, 1}, orz[tot] = St{y1, x1, x2, 1};
    sto[++tot] = St{x2, y1, y2, 0}, orz[tot] = St{y2, x1, x2, 0};
  }
  sort(sto + 1, sto + tot + 1, compare);
  sort(orz + 1, orz + tot + 1, compare);

  for (int i = 1; i <= tot; i++) {
    if (sto[i].flag) {
      for (int j = sto[i].y1; j < sto[i].y2; j++) {
        if (!arr1[j + base]) {
          ans++;
        }
        arr1[j + base]++;
      }
    } else {
      for (int j = sto[i].y1; j < sto[i].y2; j++) {
        arr1[j + base]--;
        if (!arr1[j + base]) {
          ans++;
        }
      }
    }
    if (orz[i].flag) {
      for (int j = orz[i].y1; j < orz[i].y2; j++) {
        if (!arr2[j + base]) {
          ans++;
        }
        arr2[j + base]++;
      }
    } else {
      for (int j = orz[i].y1; j < orz[i].y2; j++) {
        arr2[j + base]--;
        if (!arr2[j + base]) {
          ans++;
        }
      }
    }
  }

  cout << ans << '\n';
  return 0;
}