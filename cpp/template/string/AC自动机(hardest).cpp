#include <bits/stdc++.h>
const int maxn = 2e6 + 5;
std::pair<int, int> edge[maxn];
char ch[maxn];
std::queue<int> q;
int head[maxn], cnt, n, trie[maxn][26], nxt[maxn], cnt_trie = 1, size[maxn], end[maxn];
void count(int from) {
  for (register int i = head[from]; i; i = edge[i].second) {
    count(edge[i].first);
    size[from] += size[edge[i].first];
  }
}
inline void add(int from, int to) {
  edge[++cnt] = std::make_pair(to, head[from]);
  head[from] = cnt;
}
inline void insert(char *s, int val) {
  int from = 1;
  for (register int i = 0, to; s[i]; i++) {
    to = s[i] - 'a';
    if (!trie[from][to]) trie[from][to] = ++cnt_trie;
    from = trie[from][to];
  }
  end[val] = from;
}
inline void build() {
  for (register int i = 0; i < 26; i++) trie[0][i] = 1;
  q.push(1);
  while (!q.empty()) {
    int from = q.front();
    q.pop();
    for (register int i = 0; i < 26; i++)
      if (trie[from][i]) {
        nxt[trie[from][i]] = trie[nxt[from]][i];
        q.push(trie[from][i]);
      } else
        trie[from][i] = trie[nxt[from]][i];
  }
}
int main() {
  scanf("%d", &n);
  for (register int i = 1; i <= n; i++) {
    scanf("%s", ch);
    insert(ch, i);
  }
  build();
  scanf("%s", ch);
  for (register int i = 0, from = 1; ch[i]; i++) {
    from = trie[from][ch[i] - 'a'];
    size[from]++;
  }
  for (register int i = 2; i <= cnt_trie; i++) add(nxt[i], i);
  count(1);
  for (register int i = 1; i <= n; i++) printf("%d\n", size[end[i]]);
  return 0;
}