#include <bits/stdc++.h>

using namespace std;

static const int kMaxN = 1e4 + 155, kMaxM = 1e7;

using ll = long long;
struct huge {
  ll value[kMaxN];
  ll operator [] (const int & cur) const {
    return value[cur];
  }
  void input () {
    char str[kMaxN];
    scanf ("%s", str);
    memset (value, 0, sizeof (value));
    int lenstr = strlen (str), j = 0;
    for (int i = lenstr - 1; i >= 0; i -= 7) {
      int cur = max (i - 6, 0), reg = 0;
      while (cur <= i) {
        reg = reg * 10 + str[cur++] - '0';
      }
      value[++j] = reg;
    }
    value[0] = j;
  }
  void output () {
    printf ("%lld", value[value[0]]);
    for (int i = value[0] - 1; i >= 1; i--) {
      printf ("%07lld", value[i]);
    }
  }

  bool operator == (const huge & another) const {
    if (value[0] != another[0]) {
      return false;
    }
    for (int i = 1; i <= value[0]; i++) {
      if (value[i] != another[i]) {
        return false;
      }
    }
    return true;
  }
  bool operator < (const huge & another) const {
    if (value[0] > another[0] || (*this) == another) {
      return false;
    } else if (value[0] < another[0]) {
      return true;
    }
    for (int i = value[0]; i >= 1; i--) {
      if (value[i] > another[i]) {
        return false;
      } else if (value[i] < another[i]) {
        return true;
      }
    }
    return true;
  }
  bool operator > (const huge & another) const {
    return (!((*this) < another)) && (!((*this) == another));
  }
  bool operator <= (const huge & another) const {
    return (*this) < another || (*this) == another;
  }
  bool operator >= (const huge & another) const {
    return (*this) > another || (*this) == another;
  }

  huge operator + (const huge & another) const {
    huge ans;
    memset (ans.value, 0, sizeof (ans.value));
    ll pos = max (value[0], another.value[0]), addtag = 0;
    for (int i = 1; i <= pos; i++) {
      ans.value[i] = value[i] + another[i] + addtag;
      addtag = ans.value[i] / kMaxM;
      ans.value[i] = ans.value[i] % kMaxM; 
    }
    if (addtag > 0) {
      ans.value[++pos] = addtag;
    }
    ans.value[0] = pos;
    return ans;
  }
  huge operator - (const huge & another) const {
    huge ans;
    memset (ans.value, 0, sizeof (ans.value));
    ll pos = value[0], minustag = 0;
    for (int i = 1; i <= pos; i++) {
      ans.value[i] = value[i] - another[i] - minustag;
      if (ans.value[i] < 0) {
        ans.value[i] += kMaxM;
        minustag = 1;
      } else {
        minustag = 0;
      }
    }
    while (ans.value[pos] == 0 && pos > 1) {
      pos--;
    }
    ans.value[0] = pos;
    return ans;
  }
  huge operator * (const int & sum) const {
    huge ans;
    memset (ans.value, 0, sizeof (ans.value));
    ll pos = value[0], addtag = 0;
    for (int i = 1; i <= pos; i++) {
      ans.value[i] = value[i] * sum + addtag;
      addtag = ans.value[i] / kMaxM;
      ans.value[i] = ans.value[i] % kMaxM;
    }
    while (addtag > 0) {
      ans.value[++pos] = addtag % kMaxM;
      addtag /= kMaxM;
    }
    while (ans.value[pos] == 0 && pos > 1) {
      pos--;
    }
    ans.value[0] = pos;
    return ans;
  }
  huge operator * (const huge & another) const {
    huge ans;
    memset (ans.value, 0, sizeof (ans.value));
    ll pos = value[0] + another[0];
    for (int i = 1; i <= value[0]; i++) {
      for (int j = 1; j <= another[0]; j++) {
        ans.value[i + j - 1] += value[i] * another[j];
        ans.value[i + j] += ans.value[i + j - 1] / kMaxM;
        ans.value[i + j - 1] = ans.value[i + j - 1] % kMaxM;
      }
    }
    while (ans.value[pos] == 0 && pos > 1) {
      pos--;
    }
    ans.value[0] = pos;
    return ans;
  }
  huge operator / (const int & sum) const {
    huge ans;
    memset (ans.value, 0, sizeof (ans.value));
    ll pos = value[0], divtag = 0;
    for (int i = pos; i >= 1; i--) {
      ans.value[i] = (divtag * kMaxM + value[i]) / sum;
      divtag = (divtag * kMaxM + value[i]) % sum;
    }
    while (ans[pos] == 0 && pos > 1) {
      pos--;
    }
    ans.value[0] = pos;
    return ans;
  }
  huge operator / (const huge & another) const {
    huge ans, tmp;
    memset (ans.value, 0, sizeof (ans.value));
    memset (tmp.value, 0, sizeof (tmp.value));
    ll pos = value[0];
    ans.value[0] = 1, ans.value[1] = 0, tmp = ans;
    if ((*this) < another) {
      return ans;
    }
    for (int i = pos; i >= 1; i--) {
      tmp = tmp * kMaxM, tmp.value[1] = value[i];
      int cur = 0;
      while (tmp > another || tmp == another) {
        tmp = tmp - another;
        cur++;
      }
      ans.value[i] = cur;
    }
    while (ans.value[pos] == 0 && pos > 1) {
      pos--;
    }
    ans.value[0] = pos;
    return ans;
  }
  int operator % (const int & sum) const {
    int pos = value[0], divtag = 0;
    for (int i = pos; i >= 1; i--) {
      divtag = (divtag * kMaxM + value[i]) % sum;
    }
    return divtag;
  }
  huge operator % (const huge & another) const {
    huge ans;
    memset (ans.value, 0, sizeof (ans.value));
    ll pos = value[0];
    ans.value[0] = 1, ans.value[1] = 0;
    if ((*this) < another) {
      return (*this);
    }
    for (int i = pos; i >= 1; i--) {
      ans = ans * kMaxM, ans.value[1] = value[i];
      while (ans > another || ans == another) {
        ans = ans - another;
      }
    }
    return ans;
  }

  huge sqrt (huge base) {
    huge onesize = {1, 1}, lft = onesize, rght = base, before = base, mid = (lft + rght) / 2, tmp = mid * mid;
    while (lft < rght) {
      if (tmp < before || tmp == before) {
        lft = mid + onesize;
      } else {
        rght = mid;
      }
      mid = (lft + rght) / 2;
      tmp = mid * mid;
    }
    if (mid * mid > before && ((mid - onesize) * (mid - onesize) < before || (mid - onesize) * (mid - onesize) == before)) {
      mid = mid - onesize;
    }
    return mid;
  }
  huge pow (huge base, huge index) {
    huge onesize = {1, 1}, ans = onesize;
    while (index >= onesize) {
      if (index % 2) {
        ans = ans * base;
      }
      base = base * base;
      index = index / 2;
    }
    return ans;
  }
} calcer, a, b;

int main () {
  a.input (), b.input ();
  calcer = a - b;
  calcer.output ();
}