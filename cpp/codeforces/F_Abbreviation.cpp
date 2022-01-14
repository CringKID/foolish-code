#include <bits/stdc++.h>

using namespace std;
const int kMaxN = 355;
int arr[kMaxN], tmp[kMaxN], n, cur, total, nxt[kMaxN], sze[kMaxN];
string str;
map <string, int> mmap;

void getnxt (int arr[], int n) {
  int cur = 0;
  nxt[1] = 0;
  for (int i = 2; i <= n; i++) {
    while (cur > 0 && arr[cur + 1] != arr[i]) {
      cur = nxt[cur];
    }
    if (arr[cur + 1] == arr[i]) {
      cur++;
    }
    nxt[i] = cur;
  }
}
int Judge (int arr[], int tmp[], int n, int m, int value) {
  int cur = 0, count = 0;
  for (int i = 1; i <= n; i++) {
    while (cur > 0 && tmp[cur + 1] != arr[i]) {
      cur = nxt[cur];
    }
    if (tmp[cur + 1] == arr[i]) {
      cur++;
    }
    if (cur == m) {
      count++;
      cur = 0;
    }
  }
  return count <= 1 ? 0 : value * count;
}

int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> str;
    if (!mmap.count (str)) {
      mmap[str] = ++cur;
    }
    arr[i] = mmap[str], sze[i] = str.length ();
    total += sze[i];
  }
  total += n - 1;

  int cnt, mmax = 0, sum;
  for (int i = 1; i <= n; i++) {
    sum = cnt = 0;
    for (int j = i; j <= n; j++) {
      tmp[++cnt] = arr[j];
      sum += sze[j];
      getnxt (tmp, cnt);
      int check = Judge (arr, tmp, n, cnt, sum + (j - i) - (j - 
        i + 1));
      mmax = max (mmax, check);
    }
  }
  cout << total - mmax << '\n';
  return 0;
}