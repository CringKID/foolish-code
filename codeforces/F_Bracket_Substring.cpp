#include <iostream>
#include <algorithm>
#include <cstring>

using ll = long long;
const ll kMaxN = 255, kMod = 1e9 + 7;

char ch[kMaxN];
ll dp1[kMaxN][kMaxN], fail[kMaxN], tag[kMaxN], next[kMaxN][kMaxN], size, n, dp2[kMaxN][kMaxN][kMaxN];

void getfail () {
  int j = 0; fail[1] = 0;
  for (int i = 2; i <= size; i++) {
    while (j > 0 && ch[j + 1] != ch[i]) {
      j = fail[j];
    }
    if (ch[j + 1] == ch[i]) {
      j++;
    }
    fail[i] = j;
  }
  for (int i = 1; i < size; i++) {
    j = i;
    for (int k = 1; k < size; k++) {
      while (j > 0 && ch[j + 1] != ch[k]) {
        j = fail[j];
      }
      if (ch[j + 1] == ch[k]) {
        j++;
      }
      if (j == size) {
        tag[i] = 1;
        break;
      }
    }
  }
}
int getnext (int now, char cur) {
  if (~next[now][cur]) {
    return next[now][cur];
  }
  ll & temp = next[now][cur];
  while (now && ch[now + 1] != cur) {
    now = fail[now];
  }
  if (ch[now + 1] == cur) {
    now++;
  }
  return temp = now; 
}

int main () {
  memset (next, -1, sizeof (next));
  using namespace std;
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  dp1[0][0] = 1;
  cin >> n >> ch + 1;
  n <<= 1, size = strlen (ch + 1);
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j <= n; j++) {
      if (j > 0) {
        dp1[i][j] += dp1[i - 1][j - 1];
      }
      dp1[i][j] = (dp1[i][j] + dp1[i - 1][j + 1]) % kMod;
    }
  }

  int mmin = 0, cur = 0;
  for (int i = 1; i <= size; i++) {
    char now = ch[i];
    if (now == '(') {
      cur--;
    } else {
      cur++;
    }
    mmin = max (mmin, cur);
  }
  getfail ();

  dp2[0][0][0] = 1;
  for (int i = 0; i <= n; i++) {
    for (int j = 0; j < size; j++) {
      for (int k = 0; k <= n; k++) {
        if (k > 0) {
          int now = getnext (j, ')');
          dp2[i + 1][now][k - 1] = (dp2[i + 1][now][k - 1] + dp2[i][j][k]) % kMod;
        }
        int now = getnext (j, '(');
        dp2[i + 1][now][k + 1] = (dp2[i + 1][now][k + 1] + dp2[i][j][k]) % kMod;
      }
    }
  }

  ll ans = 0;
  for (int i = 0; i <= n - size; i++) {
    int now = n - size - i;
    for (int j = 0; j < size; j++) {
      if (tag[j]) {
        continue;
      }
      for (int k = mmin; k <= n && k - cur <= n; k++) {
        ans = (ans + 1ll * dp2[i][j][k] * dp1[now][k - cur]) % kMod;
      }
    }
  }
  cout << ans << '\n';
  return 0;
}