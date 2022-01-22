// 狂狼电竞俱乐部 | 胖头鱼
#include <iostream>
#include <vector>

using namespace std;

const int kMaxN = 1e5 + 3;

struct V {
  int c[2], v, t, r;  // 儿子、值、子树大小、翻转标记
} v[kMaxN];
int n, m, r = 1, x, y, rs;
vector<int> l;

void ReCalc(int x) {                                    // 重新计算节点
  v[x].t = v[v[x].c[0]].t + v[v[x].c[1]].t + (x != 0);  // 空子树不计算
}

void CheckR(int x) {  // 检查翻转标记
  if (v[x].r) {
    v[v[x].c[0]].r ^= 1, v[v[x].c[1]].r ^= 1;  // 下放翻转标记
    swap(v[x].c[0], v[x].c[1]);                // 交换儿子
    v[x].r = 0;                                // 清空标记
  }
}

void Rotate(int &x, bool d) {              // 旋转
  int y = v[x].c[d];                       // 记录儿子
  v[x].c[d] = v[y].c[!d], v[y].c[!d] = x;  // 重置父亲与儿子的关系
  ReCalc(x), ReCalc(y);                    // 计算儿子与父亲
  x = y;                                   // 换新的根
}

void Balance(int &x, bool d) {  // 平衡
  l.push_back(d);
  if (l.size() != 2 && x != rs) {  // 没到2层且没到目标
    return;
  }
  if (l.size() == 2) {                              // 优先2层旋转
    Rotate(l[0] == l[1] ? x : v[x].c[l[1]], l[0]);  // 同边先转当前节点，非同边先转儿子
  }
  Rotate(x, l.back());  // 将儿子转到根
  l.clear();
}

void Find(int &x, int y) {  // 找第y大的数
  CheckR(x);                // 检测翻转标记
  int t = v[v[x].c[0]].t + 1;
  if (y != t) {      // 尚未找到目标
    bool d = y > t;  // 判断查找方向
    Find(v[x].c[d], y -= d * t);
    Balance(x, d);
  }
}

void Init() {                         // 初始化，两头增加两个节点
  for (int i = 1; i <= n + 1; i++) {  // 初始化成链
    v[i] = {0, i + 1, i - 1, n + 3 - i};
  }
  v[n + 2].t = 1;
}

void Print(int x) {  // 输出
  if (!x) {          // 空节点不输出
    return;
  }
  CheckR(x);              // 检查翻转标记
  Print(v[x].c[0]);       // 输出左子树
  cout << v[x].v << " ";  // 输出当前节点
  Print(v[x].c[1]);       // 输出右子树
}

void Make(int x, int y) {              // 构造区间
  rs = r, Find(r, y + 2);              // 右界外转到根
  rs = v[r].c[0], Find(v[r].c[0], x);  // 左界外转到根的左儿子
}

int main() {
  cin >> n >> m;
  Init();  // 初始化
  for (int i = 1; i <= m; i++) {
    cin >> x >> y;
    Make(x, y);
    v[v[v[r].c[0]].c[1]].r ^= 1;  // 翻转区间
  }
  Make(1, n);
  Print(v[v[r].c[0]].c[1]);
  return 0;
}