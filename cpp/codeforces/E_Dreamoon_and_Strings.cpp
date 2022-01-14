#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
using ll = long long;
const int kMaxS = 2e3 + 5, kMaxT = 555;

char strS[kMaxS], strT[kMaxT];
int minlen[kMaxS], dp[kMaxS][kMaxS];
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> strS >> strT;
  int lenS = strlen (strS), lenT = strlen (strT);
  for (int i = 0; i < lenS; i++) {
    int index = i;
    bool fail = false;
    for (int j = 0; j < lenT; j++, index++) {
      while (index < lenS && strS[index] != strT[j]) {
        index++;
      }
      if (index == lenS) {
        fail = true;
        break;
      }
    }
    if (!fail) {
      minlen[i] = index - i;
    } else {
      minlen[i] = -1;
    }
  }

  memset (dp, 0, sizeof (dp));
  for (int i = 0; i < lenS; i++) {
    for (int j = 0; j <= i; j++) {
      dp[i + 1][j] = max (dp[i + 1][j], dp[i][j]);
      dp[i + 1][j + 1] = max (dp[i + 1][j + 1], dp[i][j]);
      if (minlen[i] != -1) {
        dp[i + minlen[i]][j + minlen[i] - lenT] = max (dp[i + minlen[i]][j + minlen[i] - lenT], dp[i][j] + 1);
      }
    }
  }
  for (int i = 0; i <= lenS; i++) {
    cout << dp[lenS][i] << ' ';
  }
  cout << '\n';
  return 0;
}