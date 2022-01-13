#include <bits/stdc++.h>

using namespace std;
using ll = long long;
const int kMaxN = 3e5 + 5, kMaxM = 1.5e7 + 5;

int arr[kMaxM], d, prime[kMaxN], n, tot, bucket[kMaxM], mmax, ans;
bool tag[kMaxM];
void findprime (int n) {
  for (int i = 2; i <= n; i++) {
    if (!tag[i]) {
      prime[++tot] = i;
    }
    for (int j = 1; j <= tot && i * prime[j] <= n; j++) {
      tag[i * prime[j]] = true;
      if (i % prime[j] == 0) {
        break;
      }
    }
  }
}

int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> arr[i];
    d = __gcd (arr[i], d);
  }
  for (int i = 1; i <= n; i++) {
    arr[i] /= d;
    mmax = max (mmax, arr[i]);
    bucket[arr[i]]++;
  }
  findprime (mmax);
  ans = n;

  for (int i = 1; i <= tot; i++) {
    int record = 0;
    for (int j = prime[i]; j <= mmax; j += prime[i]) {
      record += bucket[j];
    }
    if (record) {
      ans = min (ans, n - record);
    }
  }
  cout << (ans == n ? -1 : ans) << '\n';
  return 0;
}