#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
const int kMaxN = 1e6 + 5;

char str[kMaxN], tmp[kMaxN];
int Rank[21][kMaxN], sa[kMaxN], rnk[kMaxN], len, now, cnt;
bool compare (const int &i, const int &j) {
  if (Rank[now - 1][i] ^ Rank[now - 1][j]) {
    return Rank[now - 1][i] < Rank[now - 1][j];
  }
  return Rank[now - 1][i + (1 << (now - 1))] < Rank[now - 1][j + (1 << (now - 1))];
}
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> str + 1, len = strlen (str + 1);
  str[len + 1] = '\0';
  for (int i = 1; i <= len; i++) {
    sa[i] = i, tmp[i] = str[i];
  }
  stable_sort (tmp + 1, tmp + len + 1);
  int k = unique (tmp + 1, tmp + len + 1) - tmp - 1;
  for (int i = 1; i <= len; i++) {
    Rank[0][i] = lower_bound (tmp + 1, tmp + k + 1, str[i]) - tmp;
  }
  for (now = 1; (1 << (now - 1)) <= len; now++) {
    stable_sort (sa + 1, sa + len + 1, compare), cnt = 0;
    for (int i = 1; i <= len; i++) {
      if (compare (sa[i], sa[i - 1]) || compare (sa[i - 1], sa[i])) {
        cnt++;
      }
      Rank[now][sa[i]] = cnt;
    }
    if (cnt == len) {
      break;
    }
  }
  for (int i = 1; i <= len; i++) {
    rnk[sa[i]] = i;
  }
  for (int i = 1; i <= len; i++) {
    cout << sa[i] << " ";
  }
  cout << endl;
  return 0;
}