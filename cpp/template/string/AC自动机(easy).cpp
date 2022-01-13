#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 5;
queue<int> q;
int trie[maxn][26], val[maxn], nxt[maxn], cnt;
inline void insert(char *ch) {
  register int now = 0, len = strlen(ch);
  for (register int i = 0, tmp; i < len; i++) {
    tmp = ch[i] - 'a';
    if (!trie[now][tmp]) trie[now][tmp] = ++cnt;
    now = trie[now][tmp];
  }
  val[now]++;
}
inline void build() {
  for (register int i = 0; i < 26; i++)
    if (trie[0][i]) nxt[trie[0][i]] = 0, q.push(trie[0][i]);
  while (!q.empty()) {
    int from;
    from = q.front();
    q.pop();
    for (register int i = 0; i < 26; i++)
      if (trie[from][i])
        nxt[trie[from][i]] = trie[nxt[from]][i], q.push(trie[from][i]);
      else
        trie[from][i] = trie[nxt[from]][i];
  }
}
inline int query(char *ch) {
  int now = 0, ans = 0, len = strlen(ch);
  for (register int i = 0; i < len; i++) {
    now = trie[now][ch[i] - 'a'];
    for (register int j = now; j && ~val[j]; j = nxt[j]) ans += val[j], val[j] = -1;
  }
  return ans;
}
int n;
char keyword[maxn];
int main() {
  scanf("%d", &n);
  for (register int i = 1; i <= n; i++) scanf("%s", keyword), insert(keyword);
  build();
  scanf("%s", keyword);
  printf("%d\n", query(keyword));
  return 0;
}