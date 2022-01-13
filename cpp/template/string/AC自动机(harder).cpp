#include <bits/stdc++.h>
const int maxn = 3e5 + 5;
std::string keyword[maxn];
int num[maxn], trie[maxn][26], nxt[maxn], ans[maxn], tmp, n, size, now, Ans;
inline void insert(std::string s, int to) {
  now = 0;
  for (register int i = 0, tmp; i < s.length(); i++) {
    tmp = s[i] - 'a';
    if (!trie[now][tmp]) trie[now][tmp] = ++size;
    now = trie[now][tmp];
  }
  num[now] = to;
}
inline void build() {
  now = 0;
  std::queue<int> q;
  for (register int i = 0; i < 26; i++)
    if (trie[0][i]) q.push(trie[0][i]), nxt[trie[0][i]] = 0;
  while (!q.empty()) {
    static int from;
    from = q.front();
    q.pop();
    for (register int i = 0, to; i < 26; i++) {
      to = trie[from][i];
      if (to)
        nxt[to] = trie[nxt[from]][i], q.push(to);
      else
        trie[from][i] = trie[nxt[from]][i];
    }
  }
}
inline void query(std::string s) {
  now = 0;
  for (register int i = 0; i < s.length(); i++) {
    now = trie[now][s[i] - 'a'];
    for (register int j = now; j; j = nxt[j]) ans[num[j]]++;
  }
}
int main() {
  while (scanf("%d", &n) != EOF && n) {
    memset(num, 0, sizeof(num)), memset(ans, 0, sizeof(ans)), memset(trie, 0, sizeof(trie)), memset(nxt, 0, sizeof(nxt));
    size = 0;
    for (register int i = 1; i <= n; i++) {
      std::cin >> keyword[i];
      insert(keyword[i], i);
    }
    build();
    std::string tmp;
    std::cin >> tmp;
    query(tmp);
    Ans = 0;
    for (register int i = 1; i <= n; i++) Ans = std::max(ans[i], Ans);
    printf("%d\n", Ans);
    for (register int i = 1; i <= n; i++)
      if (ans[i] == Ans) std::cout << keyword[i] << '\n';
  }
  return 0;
}