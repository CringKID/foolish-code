#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
const int kMaxN = 2e3 + 5;

bool tag[kMaxN];
string str[kMaxN];
int n, rec[kMaxN], m;
bool checkp (int tl, int tr) {
  for (int i = 0; i < str[tl].size (); i++) {
    if (str[tl][i] != str[tr][i]) {
      return false;
    }
  }
  return true;
}
bool checks (int tl, int tr) {
  for (int i = 0; i < str[tl].size (); i++) {
    if (str[tl][str[tl].size () - i - 1] != str[tr][str[tr].size () - i - 1]) {
      return false;
    }
  }
  return true;
}
char encode (int k) {
  return (rec[k] == 1 ? 'P' : 'S');
}
int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n, m = (n - 1) * 2;
  for (int i = 1; i <= m; i++) {
    cin >> str[i];
  }
  memset (rec, -1, sizeof (rec));
  memset (tag, false, sizeof (tag));
  int tl = -1, tr = -1;
  for (int i = 1; i <= m; i++) {
    if (str[i].size () == n - 1) {
      if (tl == -1) {
        tl = i;
      } else {
        tr = i;
      }
    }
  }
  for (int i = 1; i <= m; i++) {
    if (!tag[str[i].size ()] && checkp (i, tl)) {
      rec[i] = 1;
      tag[str[i].size ()] = true;
    }
  }
  bool judgement = true;
  int tot = 0;
  for (int i = 1; i <= m; i++) {
    if (rec[i] == -1) {
      tot++;
    }
  }
  if (tot != n - 1) {
    judgement = false;
  } else {
    for (int i = 1; i <= m; i++) {
      if (rec[i] == -1 && !checks (i, tr)) {
        judgement = false;
        break;
      }
    }
  }
  if (judgement) {
    for (int i = 1; i <= m; i++) {
      cout << encode (i);
    }
    return 0;
  } else {
    memset (rec, -1, sizeof (rec));
    memset (tag, false, sizeof (tag));
    for (int i = 1; i <= m; i++) {
      if (!tag[str[i].size ()] && checkp (i, tr)) {
        rec[i] = 1;
        tag[str[i].size ()] = true;
      }
    }
    for (int i = 1; i <= m; i++) {
      cout << encode (i);
    }
    return 0;
  }
  return 0;
} //resubmit