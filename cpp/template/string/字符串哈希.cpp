#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e4 + 5;
typedef unsigned long long ll;

ll Base = 131ll, Array[maxn], mod = 212370440130137957ll;
char ch[maxn];
int n, Ans = 1, Prime = 233317;

ll Hash(char ch[]) {
  int Len = strlen(ch);
  ll Ans = 0;
  for (int i = 0; i < Len; i++) Ans = (Ans * Base + (ll)ch[i]) % mod + Prime;
  return Ans;
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) scanf("%s", ch), Array[i] = Hash(ch);
  sort(Array + 1, Array + n + 1);

  for (int i = 1; i < n; i++)
    if (Array[i] != Array[i + 1]) Ans++;
  return printf("%u\n", Ans) & 0;
}