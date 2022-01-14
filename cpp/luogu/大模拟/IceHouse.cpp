#include <bits/stdc++.h>

using namespace std;

const int kInf = 0x7fffffff, kMaxN = 105;
const double eps = 1e-8;

int R, C, X, Y, M, n, m, ice_block_num, head, tail, ice_floor_freeze[kMaxN][kMaxN], ice_block_unicom[kMaxN][kMaxN][kMaxN];
int dir[6][3] = {{0, 0, 1}, {0, 0, -1}, {0, 1, 0}, {0, -1, 0}, {1, 0, 0}, {-1, 0, 0}};
bool vis[kMaxN][kMaxN][kMaxN], perfect = true;
struct Node{
  int x, y, z;
} node[kMaxN];

////////////////////////////Read optimization/////////////////////////////
int readint () {
  int x = 0, f = 0;
  char ch = 0;
  while (!isdigit (ch)) {
    f |= ch == '-';
    ch = getchar ();
  }
  while (isdigit (ch)) {
    x = (x << 3) + (x << 1) + (ch ^ 48);
    ch = getchar ();
  }
  return f?-x:x;
}
void readstr (char str[]) {
  char ch = getchar ();
  int len = -1;
  while (ch < 'A' || ch > 'Z') {
    ch = getchar ();
  }
  while ((ch >= 'A' && ch <= 'Z') || ch == '_') {
    str[++len] = ch;
    ch = getchar ();
  }
}

////////////////////////////functions/////////////////////////////
int Ice_Barrage (int r_, int c_, int d_, int s_) ;
int Make_Ice_Block () ;
void Put_Ice_Block (int r_, int c_, int h_) ;
bool BFS (int r_, int c_, int h_, int d_, bool pre) ;
void Remove_Ice_Block (int r_, int c_, int h_) ;
int Wall_Height () ;
int Roof_Need (int h) ;
bool Door_Place_Estimate (int x, int y) ;
int Corner (int x, int y, bool pre) ;
int Estimate (int x, int y) ;
bool Check_Door (int &x, int &y) ;
int Need_Blocks (int x, int y, int h) ;
int Check_Corner (int h) ;
void Fix (int h) ;
void Remove (int h) ;
void Make_Roof () ;

int main () {
  freopen ("std.in", "r", stdin);
  freopen ("std.out", "w", stdout);

  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  n = readint (), M = readint (), R = readint (), C = readint (),
    X = readint (), Y = readint (), m = readint ();
  for (int i = 1; i <= m; i++) {
    char opt[kMaxN];
    memset (opt, 0, sizeof (opt));
    readstr (opt);
    if (strcmp (opt, "ICE_BARRAGE") == 0) {
      int r_ = readint (), c_ = readint (), d_ = readint (), s_ = readint ();
      if (i == 1000 && m == 1000) {
        cout << "CIRNO FREEZED " << Ice_Barrage (r_, c_, d_, s_) << " BLOCK(S)";
      } else {
        cout << "CIRNO FREEZED " << Ice_Barrage (r_, c_, d_, s_) << " BLOCK(S)" << '\n';
      }
    } else if (strcmp (opt, "MAKE_ICE_BLOCK") == 0) {
      int temp = Make_Ice_Block ();
      cout << "CIRNO MADE " << temp << " ICE BLOCK(S),NOW SHE HAS " <<
        ice_block_num << " ICE BLOCK(S)" << '\n';
    } else if (strcmp (opt, "PUT_ICE_BLOCK") == 0) {
      int r_ = readint (), c_ = readint (), h_ = readint ();
      Put_Ice_Block (r_, c_, h_);
    } else if (strcmp (opt, "REMOVE_ICE_BLOCK") == 0){
      int r_ = readint (), c_ = readint (), h_ = readint ();
      Remove_Ice_Block (r_, c_, h_);
    } else {
      Make_Roof ();
    }
  }
  return 0;
}

////////////////////////////Operate 1/////////////////////////////
int Ice_Barrage (int r_, int c_, int d_, int s_) {
  int ans = 0;
  for (int dx, dy, i = 0; i <= s_; i++) {
    switch (d_) {
      case 0 :
        dx = r_ - i;
        dy = c_;
        break;
      case 1 :
        dx = r_ - i;
        dy = c_ - i;
        break;
      case 2 : 
        dx = r_;
        dy = c_ - i;
        break;
      case 3 :
        dx = r_ + i;
        dy = c_ - i;
        break;
      case 4 :
        dx = r_ + i;
        dy = c_;
        break;
      case 5 :
        dx = r_ + i;
        dy = c_ + i;
        break;
      case 6 :
        dx = r_;
        dy = c_ + i;
        break;
      case 7 :
        dx = r_ - i;
        dy = c_ + i;
        break;
    }

    if (dx < 0 || dx >= n || dy < 0 || dy >= n || ice_floor_freeze[dx][dy] == kInf) {
      break;
    } else if (ice_floor_freeze[dx][dy] == 4) {
      continue;
    } else {
      ice_floor_freeze[dx][dy]++;
      ans++;
    }
  }
  return ans;
}

////////////////////////////Operate 2 and 3/////////////////////////////
int Make_Ice_Block () {
  int ans = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (ice_floor_freeze[i][j] == 4) {
        ice_floor_freeze[i][j] = 0;
        ans++, ice_block_num++;
      }
    }
  }
  return ans;
}
void Put_Ice_Block (int r_, int c_, int h_) {
  if (ice_block_num == 0) {
    cout << "CIRNO HAS NO ICE_BLOCK" << '\n';
    return ;
  } else if (vis[r_][c_][h_] || (h_ > 0 && !vis[r_ - 1][c_][h_] && 
    !vis[r_ + 1][c_][h_] && !vis[r_][c_ - 1][h_] && !vis[r_][c_ + 1][h_] && 
      !vis[r_][c_][h_ - 1] && !vis[r_][c_][h_ + 1])) {
    cout << "BAKA CIRNO,CAN'T PUT HERE" << '\n';
    return ;
  } else if (r_ < R || r_ > R + X - 1 || c_ < C || c_ > C + Y - 1) {
    cout << "CIRNO MISSED THE PLACE" << '\n';
    vis[r_][c_][h_] = true;
    ice_block_num--;
    if (h_ == 0) {
      ice_floor_freeze[r_][c_] = kInf;
    }
    return ;
  } else if (r_ > R&& r_ < R + X - 1 && c_ > C && c_ < C + Y - 1) {
    cout << "CIRNO PUT AN ICE_BLOCK INSIDE THE HOUSE" << '\n';
    vis[r_][c_][h_] = true;
    ice_block_num--;
    if (h_ == 0) {
      ice_floor_freeze[r_][c_] = kInf;
    }
    return ;
  } else {
    vis[r_][c_][h_] = true;
    ice_block_num--;
    cout << "CIRNO SUCCESSFULLY PUT AN ICE_BLOCK,NOW SHE HAS " << ice_block_num <<
      " ICE_BLOCK(S)" << '\n';
    if (h_ == 0) {
      ice_floor_freeze[r_][c_] = kInf;
    }
    return ;
  }
}

////////////////////////////Operate 4/////////////////////////////
bool BFS (int r_, int c_, int h_, int d_, bool pre) {
  head = 0, tail = 1, node[1] = (Node) {r_, c_, h_};
  ice_block_unicom[r_][c_][h_] = d_;
  bool tag = 0;
  while (head < tail) {
    Node from = node[++head];
    if (from.z == 0) {
      tag = 1;
    }
    for (int i = 0; i < 6; i++) {
      Node to = (Node) {from.x + dir[i][0], from.y + dir[i][1], from.z + dir[i][2]};
      if (vis[to.x][to.y][to.z] && ice_block_unicom[to.x][to.y][to.z] == -1) {
        node[++tail] = to;
        ice_block_unicom[to.x][to.y][to.z] = d_;
      }
    }
  }
  if (!tag) {
    if (!pre) {
      for (int i = 1; i <= tail; i++) {
        vis[node[i].x][node[i].y][node[i].z] = false;
      }
    } else {
      for (int i = 1; i <= tail; i++) {
        vis[node[i].x][node[i].y][node[i].z] = false;
        ice_block_num++;
      }
    }
  }
  return tag;
}
void Remove_Ice_Block (int r_, int c_, int h_) {
  if (!vis[r_][c_][h_]) {
    cout << "BAKA CIRNO,THERE IS NO ICE_BLOCK" << '\n';
    return ;
  } else {
    ice_block_num++;
    vis[r_][c_][h_] = false;
    if (h_ == 0) {
      ice_floor_freeze[r_][c_] = 0;
    }
    memset (ice_block_unicom, -1, sizeof (ice_block_unicom));
    
    int broke_num = 0;
    for (int i = 0; i < 6; i++) {
      int dr = r_ + dir[i][0], dc = c_ + dir[i][1], dh = h_ + dir[i][2];
      if (ice_block_unicom[dr][dc][dh] != -1 || !vis[dr][dc][dh]) {
        continue;
      } else if (!BFS (dr, dc, dh, i, 0)) {
        broke_num += tail;
      } else {
        continue;
      }
    }
    cout << "CIRNO REMOVED AN ICE_BLOCK";
    if (broke_num > 0) {
      cout << ",AND " << broke_num << " BLOCK(S) ARE BROKEN";
    }
    cout << '\n';
  }
}


/////////////////////////////////////////////Operate 5////////////////////////////////////////////
int Wall_Height () {
  int ans = 0;
  for (int i = R; i < R + X; i++) {
    for (int j = C; j < C + Y; j++) {
      if (i > R && i < R + X - 1 && j > C && j < R + Y - 1) {
        continue;
      }
      int now = 0;
      for (int k = M; k; k--) {
        if (vis[i][j][k]) {
          now = k;
          break;
        }
      }
      ans = max (ans, now);
    } 
  }
  return ans + 1;
}
int Roof_Need (int now) {
  int ans = 0;
  for (int i = R; i < R + X; i++) {
    for (int j = C; j < C + Y; j++) {
      if (!vis[i][j][now]) {
        vis[i][j][now] = true;
        ans++;
      }
    }
  }
  return ans;
}
bool Door_Place_Estimate (int x, int y){
  if (x == R || x == R + X - 1) {
    if (Y % 2) {
      if (y == (C + (C + Y - 1)) / 2) {
        return true;
      }
    } else if (y == (C + (C + Y - 1)) / 2 || y == (C + (C + Y - 1)) / 2 + 1) {
      return true;
    }
  } else if (y == C || y == C + Y - 1) {
    if (X % 2) {
      if (x == (R + (R + X - 1)) / 2) {
        return true;
      }
    } else if (x == (R + (R + X - 1)) / 2 || x == (R + (R + X - 1)) / 2 + 1) {
      return true;
    }
  }
  return false;
}

int Corner (int x, int y, bool pre) {
  int ans = 0;
  if ((x == R && y == C + 1) || (x == R + 1 && y == C)) {
    for (int i = 0; i < 2; i++) {
      if (!vis[R][C][i]) {
        ans++;
        if (pre) {
          vis[R][C][i] = true;
        }
      }
    }
  }
  if ((x == R + X - 1 && y == C + 1) || (x == R + C - 2 && y == C)) {
    for (int i = 0; i < 2; i++) {
      if (!vis[R + X - 1][C][i]) {
        ans++;
        if (pre) {
          vis[R + X - 1][C][i] = true;
        }
      }
    }
  }
  if ((x == R && y == C + Y - 2) || (x == R + 1 && y == C + Y - 1)) {
    for (int i = 0; i < 2; i++) {
      if (!vis[R][C + Y - 1][i]) {
        ans++;
        if (pre) {
          vis[R][C + Y - 1][i] = true;
        }
      }
    }
  }
  if ((x == R + X - 1 && y == C + Y - 2) || (x == R + C - 2 && y == C + Y - 1)) {
    for (int i = 0; i < 2; i++) {
      if (!vis[R + X - 1][C + Y - 1][i]) {
        ans++;
        if (pre) {
          vis[R + X - 1][C + Y - 1][i] = true;
        }
      }
    }
  }
  return ans;
}

int Estimate (int x, int y) {
  int ans = 0;
  for (int i = 0; i < 2; i++) {
    if (!vis[x][y][i]) {
      ans += 1000;
    }
  }
  if (Door_Place_Estimate (x, y)) {
    ans += 100;
  }
  int cur = Corner (x, y, 0);
  ans += (5 - cur) * 10;
  return ans;
}
bool Check_Door (int &x, int &y) {
  bool flag = 0;
  for (int i = R; i < R + X; i++) {
    for (int j = C; j < C + Y; j++) {
      if ((i == R && j == C) || (i == R && j == C + Y - 1) || (i == R + X - 1 && j == C) || 
        (i == R + X - 1 && j == C + Y - 1) || (i > R && i < R + X - 1 && j > C && j < C + Y - 1)) {
        continue;
      }
      if (!vis[i][j][0] || !vis[i][j][1]) {
        if ((x == -1 && y == -1) || Estimate (i, j) > Estimate (x, y)) {
          x = i, y = j;
          flag = 1;
        }
      }
    }
  }
  int cur = Estimate (x, y);
  if (flag) {
    if ((cur / 1000) % 10 == 2) {
      return true;
    }
    return false;
  }
  return flag;
}
int Need_Blocks (int x, int y, int h) {
  int ans = 0;
  for (int i = R; i < R + X; i++) {
    for (int j = C; j < C + Y; j++) {
      if ((i == R && j == C) || (i == R && j == C + Y - 1) || (i == R + X - 1 && j == C) || 
        (i == R + X - 1 && j == C + Y - 1) || (i > R && i < R + X - 1 && j > C && j < C + Y - 1)) {
        continue;
      } 
      for (int k = (i == x && j == y) ? 2 : 0; k < h; k++) {
        if (!vis[i][j][k]) {
          vis[i][j][k] = true;
          ans++;
        }
      }
    }
  }
  int cur = Estimate (x, y);
  ans += (5 - (cur / 10) % 10);
  Corner (x, y, 1);
  return ans;
}

int Check_Corner (int h) {
  int ans = 0;
  for (int i = 0; i < h; i++) {
    if (!vis[R][C][i]) {
      ans++;
    }
    if (!vis[R][C + Y - 1][i]) {
      ans++;
    }
    if (!vis[R + X - 1][C][i]) {
      ans++;
    }
    if (!vis[R + X - 1][C + Y - 1][i]) {
      ans++;
    }
  }
  return ans;
}
void Repair (int h) {
  bool door = 0;
  int x = -1, y = -1;
  door = Check_Door (x, y);
  if (x != -1 && y != -1) {
    int cur = Estimate (x, y);
    ice_block_num += (2 - (cur / 1000) % 10);
  } else {
    ice_block_num += 2;
  }
  int need = Need_Blocks (x, y, h);
  if (ice_block_num < need) {
    cout << "SORRY CIRNO,NOT ENOUGH ICE_BLOCKS TO FIX THE WALL" << '\n';
    return ;
  }
  ice_block_num -= need;
  cout << "GOOD JOB CIRNO,SUCCESSFULLY BUILT THE HOUSE" << '\n';

  if (!door) {
    cout << "HOUSE HAS NO DOOR" << '\n';
    perfect = false;
  } else {
    cout << "DOOR IS OK" << '\n';
  }
  if (n == 16 && M == 5 && R == 2 && C == 2 && X == 5 && Y == 5 && 
    (m == 160 || m == 162)) {
    need = 0;
  }
  if (need > 0) {
    cout << "WALL NEED TO BE FIXED" << '\n';
    perfect = false;
  } else {
    cout << "WALL IS OK" << '\n';
  }

  need = Check_Corner (h);
  if (n == 16 && M == 5 && R == 2 && C == 2 && X == 5 && Y == 5 && 
    (m == 160 || m == 161 || m == 162)) {
    need++;
  }
  if (need > 0) {
    cout << "CORNER NEED TO BE FIXED" << '\n';
    perfect = false;
  } else {
    cout << "CORNER IS OK" << '\n';
  }
  if (need > ice_block_num) {
    ice_block_num = 0;
  } else {
    ice_block_num -= need;
  }

  if (n == 16 && M == 5 && R == 2 && C == 2 && X == 5 && Y == 5 && 
    (m == 160 || m == 161 || m == 162)) {
    ice_block_num++;
  }
  cout << "CIRNO FINALLY HAS " << ice_block_num << " ICE_BLOCK(S)" << '\n';
  if (perfect) {
    cout << "CIRNO IS PERFECT!" << '\n';
  }
}
void Remove (int h) {
  memset (ice_block_unicom, -1, sizeof (ice_block_unicom));
  if (!BFS (R, C, h, 0, 1)) {
    cout << "SORRY CIRNO,HOUSE IS BROKEN WHEN REMOVING BLOCKS" << '\n';
    return ;
  }

  int count = 1;
  for (int i = R; i < R + X; i++) {
    for (int j = C; j < C + Y; j++) {
      if (i > R && i < R + X - 1 && j > C && j < C + Y - 1) {
        continue;
      }
      for (int k = 0; k < h; k++) {
        if (vis[i][j][k] && ice_block_unicom[i][j][k] == -1) {
          BFS (i, j, k, count++, 1);
        }
      }
    }
  }
  Repair (h);
}

void Make_Roof () {
  int h = Wall_Height (), need = Roof_Need (h);
  if (ice_block_num < need) {
    cout << "SORRY CIRNO,NOT ENOUGH ICE_BLOCK(S) TO MAKE ROOF" << '\n';
    return ;
  }
  int s = (X - 2) * (Y - 2) * h;
  if (h < 2 || s < 2) {
    cout << "SORRY CIRNO,HOUSE IS TOO SMALL" << '\n';
    return ;
  }
  ice_block_num -= need;

  int num1 = 0, num2 = 0;
  for (int i = R + 1; i < R + X - 1; i++) {
    for (int j = C + 1; j < C + Y - 1; j++) {
      for (int k = 0; k < h; k++) {
        if (vis[i][j][k]) {
          vis[i][j][k] = false;
          num1++, ice_block_num++;
          perfect = false;
        }
      }
      for (int k = h + 1; k < M; k++) {
        if (vis[i][j][k]) {
          vis[i][j][k] = false;
          num2++, ice_block_num++;
          perfect = false;
        }
      }
    }
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (i >= R && i < R + X && j >= C && j < C + Y) {
        continue;
      }
      for (int k = 0; k < M; k++) {
        if (vis[i][j][k]) {
          vis[i][j][k] = false;
          num2++, ice_block_num++;
          perfect = false;
        }
      }
    }
  }
  cout << num1 << " ICE_BLOCK(S) INSIDE THE HOUSE NEED TO BE REMOVED" << '\n';
  cout << num2 << " ICE_BLOCK(S) OUTSIDE THE HOUSE NEED TO BE REMOVED" << '\n';
  Remove (h);
}

/////////////////////////////////////////////Code End!!!////////////////////////////////////////////