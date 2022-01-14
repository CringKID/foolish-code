#include <bits/stdc++.h>

using namespace std;
const double eps = 1e-7;
const int kMaxN = 55, dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
struct Line {
  double cur, bol, left, right;
  int tag;
  Line (double cur_, double bol_, double left_, double right_, int tag_) : 
    cur (cur_), bol (bol_), left (left_), right (right_), tag (tag_) {
  }
  Line () {
  }
} ;
struct Spot {
  int from, to;
  Spot (int from_, int to_) : from (from_), to (to_) {
  }
  Spot () {
  }
} spot[kMaxN];
struct Ant {
  Spot spot, last;
  int health, maxhealth, age, level;
  Ant (Spot spot_, Spot last_, int health_, int maxhealth_, int age_, int level_) :
    spot (spot_), last (last_), health (health_), maxhealth (maxhealth_), age 
    (age_), level (level_) {
  }
  Ant () {
  }
} ;
bool Equal (const double s1, const double s2) {
  return fabs (s1 - s2) <= eps;
}
bool Less (const double s1, const double s2) {
  return s2 - s1 > eps;
}
bool EOL (const double s1, const double s2) {
  return Equal (s1, s2) || Less (s1, s2);
}
double Dist (Spot s1, Spot s2) {
  return sqrt ((s1.from - s2.from) * (s1.from - s2.from) + (s1.to - s2.to) * 
    (s1.to - s2.to));
}
Line Getmean (Spot s1, Spot s2) {
  if (s1.from == s2.from) {
    return Line (s1.from, 0, min (s1.to, s2.to), max (s1.to, s2.to), 1);
  } else {
    double cur = 1.0 * (s1.to - s2.to) / (s1.from - s2.from);
    return Line (cur, s1.to - cur * s1.from, min (s1.from, s2.from), max (s1.from, 
      s2.from), 0);
  }
}
bool Judge (Line line, Spot spot) {
  if (!line.tag) {
    if ((2 * line.cur * line.bol - 2 * spot.to * line.cur - 2 * spot.from) * 
      (2 * line.cur * line.bol - 2 * spot.to * line.cur - 2 * spot.from) - 4 * 
      (line.cur * line.cur + 1) * (spot.from * spot.from + line.bol * line.bol - 
      2 * spot.to * line.bol + spot.to * spot.to - 1.0 / 4.0) < 0) {
      return false;
    }
    double cur1 = -(2 * line.cur * line.bol - 2 * spot.to * line.cur - 2 * 
      spot.from), cur2 = sqrt ((2 * line.cur * line.bol - 2 * spot.to * line.cur - 
      2 * spot.from) * (2 * line.cur * line.bol - 2 * spot.to * line.cur - 2 * 
      spot.from) - 4 * (line.cur * line.cur + 1) * (spot.from * spot.from + 
      line.bol * line.bol - 2 * spot.to * line.bol + spot.to * spot.to - 1.0 / 4.0)),
      cur3 = 2 * (line.cur * line.cur + 1);
    return (EOL (line.left, (cur1 + cur2) / cur3) && EOL ((cur1 + cur2) / cur3, 
      line.right) || EOL (line.left, (cur1 - cur2) / cur3) && EOL ((cur1 - 
      cur2) / cur3, line.right));
  } else {
    if ((line.cur - spot.from) * (line.cur - spot.from) > 1.0 / 4.0) {
      return false;
    }
    int cur = sqrt (1.0 / 4.0 - (line.cur - spot.from) * (line.cur - spot.from));
    return (EOL (line.left, spot.to + cur) && EOL (spot.to + cur, line.right) || 
    EOL (line.left, spot.to - cur) && EOL (spot.to - cur, line.right));
  }
}
int n, m, s, d, r, t, mat[kMaxN][kMaxN], mmap[kMaxN][kMaxN], tots, tag = -1;
vector <Ant> ve;
double quickpow (double base, int index) {
  double ans = 1;
  while (index) {
    if (index & 1) {
      ans *= base;
    }
    base *= base;
    index >>= 1;
  }
  return ans;
}

void Spawn () {
  if (mmap[0][0]) {
    return ;
  }
  for (int i = 0; i < ve.size (); i++) {
    if (ve[i].spot.from == 0 && ve[i].spot.to == 0) {
      return ;
    }
  }
  tots++;
  int cur = (int)(4.0 * quickpow (1.1, (tots + 5) / 6));
  ve.emplace_back (Spot (0, 0), Spot (0, 0), cur, cur, 0, (tots + 5) / 6);
}
void Putidentity () {
  for (int i = 0; i < ve.size (); i++) {
    mat[ve[i].spot.from][ve[i].spot.to] += (tag == i ? 5 : 2);
  }
}
bool Nothing (int x, int y) {
  if (mmap[x][y]) {
    return false;
  }
  for (int i = 0; i < ve.size (); i++) {
    if (ve[i].spot.from == x && ve[i].spot.to == y) {
      return false;
    }
  }
  return true;
}
bool Check (int identity, int x, int y) {
  return (x != ve[identity].last.from || y != ve[identity].last.to) && 0 <= x && 
    x <= n && 0 <= y && y <= m && Nothing (x, y);
}
void Partmove (int identity, int x, int y) {
  ve[identity].last = ve[identity].spot;
  ve[identity].spot = Spot (x, y);
}
void Move () {
  for (int i = 0; i < ve.size (); i++) {
    int pans = -1, tval, tx, ty;
    for (int j = 0; j < 4; j++) {
      tx = ve[i].spot.from + dir[j][0];
      ty = ve[i].spot.to + dir[j][1];
      if (Check (i, tx, ty) && mat[tx][ty] > pans) {
        pans = mat[tx][ty];
        tval = j;
      }
    }
    if (pans < 0) {
      ve[i].last = ve[i].spot;
      continue;
    } else {
      if ((ve[i].age + 1) % 5 == 0) {
        do {
          tval = (tval + 3) % 4;
        } while (!Check (i, ve[i].spot.from + dir[tval][0], ve[i].spot.to + 
          dir[tval][1])) ;
      }
      Partmove (i, ve[i].spot.from + dir[tval][0], ve[i].spot.to + dir[tval][1]);
    }
  }
}
void Shoot (Spot from, Spot to) {
  Line k = Getmean (from, to);
  for (int i = 0; i < ve.size (); i++) {
    if (Judge (k, ve[i].spot)) {
      ve[i].health -= d;
    }
    // cout << ve[i].health << "SHOOT\n";
  }
}
void Attack () {
  for (int i = 1; i <= s; i++) {
    if (tag != -1 && EOL (Dist (spot[i], ve[tag].spot), (double) r)) {
      Shoot (spot[i], ve[tag].spot);
    } else {
      double QAQ = r + 1, QWQ;
      int SAD;
      for (int j = 0; j < ve.size (); j++) {
        QWQ = Dist (spot[i], ve[j].spot);
        if (Less (QWQ, QAQ)) {
          QAQ = QWQ;
          SAD = j;
        }
      }
      if (EOL (QAQ, r)) {
        Shoot (spot[i], ve[SAD].spot);
      }
    }
  }
}

int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> n >> m >> s >> d >> r;
  for (int i = 1, tmp1, tmp2; i <= s; i++) {
    cin >> tmp1 >> tmp2;
    spot[i] = Spot (tmp1, tmp2);
    mmap[tmp1][tmp2] = 1;
  }
  cin >> t;
  for (int Times = 1; Times <= t; Times++) {
    if (ve.size () < 6) {
      Spawn ();
    }
    Putidentity (), Move ();
    for (int i = 0; i < ve.size (); i++) {
      if (ve[i].spot.from == n && ve[i].spot.to == m && tag == -1) {
        tag = i;
        ve[i].health = min (ve[i].maxhealth, ve[i].health + ve[i].maxhealth / 2);
      }
      // cout << ve[i].health << "MAIN\n";
    }
    Attack ();
    for (int i = 0; i < ve.size (); i++) {
      if (ve[i].health < 0) {
        ve.erase (ve.begin () + i);
        if (tag == i) {
          tag = -1;
        }
        if (tag > i) {
          tag--;
        }
        i--;
      }
    }
    for (int i = 0; i < ve.size (); i++) {
      if (tag == i && ve[i].spot.from == 0 && ve[i].spot.to == 0) {
        cout << "Game over after " << Times << " seconds\n" << ve.size () << '\n';
        for (int j = 0; j < ve.size (); j++) {
          cout << ve[j].age << ' ' << ve[j].level << ' ' << ve[j].health << ' ' << 
            ve[j].spot.from << ' ' << ve[j].spot.to << '\n';
        }
        return 0;
      }
    }
    for (int i = 0; i <= n; i++) {
      for (int j = 0; j <= m; j++) {
        if (mat[i][j]) {
          mat[i][j]--;
        }
      }
    }
    for (int i = 0; i < ve.size (); i++) {
      ve[i].age++;
    }
  }
  
  cout << "The game is going on\n" << ve.size () << '\n';
  for (int i = 0; i < ve.size (); i++) {
    cout << ve[i].age << ' ' << ve[i].level << ' ' << ve[i].health << ' ' << 
      ve[i].spot.from << ' ' << ve[i].spot.to << '\n';
  }
  return 0;
}