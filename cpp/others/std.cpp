#include <iostream>
#include <algorithm>
#include <sstream>

using namespace std;
const int kMaxN = 1e5 + 5;

int tree[kMaxN * 50][27], tot, End[kMaxN], cur = 1;
void insert (string str) {
  int rec = 0;
  for (int i = 0; i < str.length (); i++) {
    int ch = str[i] - 'a';
    if (!tree[rec][ch]) {
      tree[rec][ch] = ++tot;
    }
    rec = tree[rec][ch];
  }
  End[rec] = cur++;
}
int query (string str) {
  int rec = 0;
  for (int i = 0; i < str.length (); i++) {
    int ch = str[i] - 'a';
    if (!tree[rec][ch]) {
      return 0;
    }
    rec = tree[rec][ch];
  }
  return End[rec];
}
string str[kMaxN];
int main () {
  int slen = 1; string s;
  while (getline (cin, s)) {
    if (s.empty ()) {
      break;
    }
    istringstream stringin (s);
    stringin >> s;
    str[slen++] = s;
    stringin >> s;
    insert (s);
  }
  while (cin >> s) {
    int ans = query (s);
    cout << (!ans ? "eh" : str[ans]) << '\n';
  }
  return 0;
}