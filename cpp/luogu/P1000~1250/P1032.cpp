#include <bits/stdc++.h>
using namespace std;
string a[10], b[10], s, t;
int n = 1;
map<string, int> A, B;
queue<string> A_, B_;
inline void init() {
  cin >> s >> t;
  while (cin >> a[n] >> b[n]) n++;
}
inline int bfs() {
  int step = 0;
  A_.push(s);
  A[s] = 0;
  B_.push(t);
  B[t] = 0;
  string s, s2;
  while (++step <= 5) {
    while (A[A_.front()] == step - 1) {
      s = A_.front();
      A_.pop();
      for (int i = 1; i <= n; i++) {
        unsigned int pos = 0;
        while (pos < s.length()) {
          if (s.find(a[i], pos) == s.npos) break;
          s2 = s;
          s2.replace(s2.find(a[i], pos), a[i].length(), b[i]);
          if (A.find(s2) != A.end()) {
            pos++;
            continue;
          }
          if (B.find(s2) != B.end()) return step * 2 - 1;
          A_.push(s2);
          A[s2] = step;
          pos++;
        }
      }
    }
    while (B[B_.front()] == step - 1) {
      s = B_.front();
      B_.pop();
      for (int i = 1; i <= n; i++) {
        unsigned int pos = 0;
        while (pos < s.length()) {
          if (s.find(b[i], pos) == s.npos) break;
          s2 = s;
          s2.replace(s2.find(b[i], pos), b[i].length(), a[i]);
          if (B.find(s2) != B.end()) {
            pos++;
            continue;
          }
          if (A.find(s2) != A.end()) return step * 2;
          B_.push(s2);
          B[s2] = step;
          pos++;
        }
      }
    }
  }
  return -1;
}
int main() {
  init();
  int ans = bfs();
  if (ans == -1)
    printf("NO ANSWER!");
  else
    printf("%d", ans);
  return 0;
}